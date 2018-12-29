// Copyright 2013 Axel Rasmussen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use crate::util::error::*;
use failure::bail;
use lazy_static::lazy_static;
use regex::Regex;
use std::cmp::Ordering;
use std::collections::BTreeSet;
use std::collections::HashMap;
use std::collections::HashSet;
use std::fmt;
use std::hash::{Hash, Hasher};
use std::str::FromStr;

#[derive(Clone, Debug)]
struct ValuePair {
    pub text: String,
    pub value: u64,
}

impl ValuePair {
    pub fn new(text: &str, value: u64) -> ValuePair {
        ValuePair {
            text: text.to_owned(),
            value: value,
        }
    }
}

impl PartialEq for ValuePair {
    fn eq(&self, other: &ValuePair) -> bool {
        self.value == other.value
    }
}

impl Eq for ValuePair {}

impl PartialOrd for ValuePair {
    fn partial_cmp(&self, other: &ValuePair) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for ValuePair {
    fn cmp(&self, other: &ValuePair) -> Ordering {
        self.value.cmp(&other.value)
    }
}

impl Hash for ValuePair {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.value.hash(state);
    }
}

lazy_static! {
    static ref OUTPUT_VALUES: BTreeSet<ValuePair> = {
        let mut s = BTreeSet::new();
        s.insert(ValuePair::new("M", 1000));
        s.insert(ValuePair::new("CM", 900));
        s.insert(ValuePair::new("D", 500));
        s.insert(ValuePair::new("CD", 400));
        s.insert(ValuePair::new("C", 100));
        s.insert(ValuePair::new("XC", 90));
        s.insert(ValuePair::new("L", 50));
        s.insert(ValuePair::new("XL", 40));
        s.insert(ValuePair::new("X", 10));
        s.insert(ValuePair::new("IX", 9));
        s.insert(ValuePair::new("V", 5));
        s.insert(ValuePair::new("IV", 4));
        s.insert(ValuePair::new("I", 1));
        s
    };
}

lazy_static! {
    static ref ROMAN_NUMERAL_VALUES: HashMap<char, u64> = {
        let mut m = HashMap::new();
        m.insert('I', 1);
        m.insert('V', 5);
        m.insert('X', 10);
        m.insert('L', 50);
        m.insert('C', 100);
        m.insert('D', 500);
        m.insert('M', 1000);
        m
    };
}

/// This function computes the numeric value of the given additive string. That
/// is, a string of numerals which contains no "subtractive pairs" (e.g., "IV"
/// = 4). Empty strings are considered valid, and are assumed to have a value
/// of 0.
fn get_additive_string_value(s: &str) -> Result<u64> {
    // If we were given an empty string, we're done.
    if s.len() == 0 {
        return Ok(0);
    }

    // Add each character's value to the total.
    let mut total: u64 = 0;
    for c in s.chars() {
        match ROMAN_NUMERAL_VALUES.get(&c) {
            Some(v) => {
                total += *v;
            }
            None => bail!("Invalid Roman numeral value '{}'", c),
        }
    }

    Ok(total)
}

/// This function computes the numeric value of the given subtractive pair
/// string. That is, the given input string should be a two-character
/// subtractive pair (e.g., "IX" = 9), or an empty string (which results in a
/// valid of 0).
fn get_subtractive_string_value(s: &str) -> Result<u64> {
    // If we were given an empty string, we're done.
    if s.len() == 0 {
        return Ok(0);
    }

    // Get the value and the subtractive value.
    if s.len() != 2 {
        bail!("Valid subtractive pairs must contain at least two numerals");
    }

    let sub: u64 = *ROMAN_NUMERAL_VALUES
        .get(&s.chars().nth(0).unwrap())
        .unwrap();
    let val: u64 = *ROMAN_NUMERAL_VALUES
        .get(&s.chars().nth(1).unwrap())
        .unwrap();
    if val < sub {
        bail!("Invalid subtractive pair '{}'", s);
    }

    Ok(val - sub)
}

#[derive(Clone, Debug, Eq, Hash, Ord, PartialEq, PartialOrd)]
pub struct RomanNumeral {
    value: u64,
}

impl RomanNumeral {
    pub fn new() -> RomanNumeral {
        RomanNumeral { value: 0 }
    }

    pub fn get_value(&self) -> u64 {
        self.value
    }
}

impl Default for RomanNumeral {
    fn default() -> Self {
        Self::new()
    }
}

impl From<u64> for RomanNumeral {
    fn from(v: u64) -> RomanNumeral {
        RomanNumeral { value: v }
    }
}

impl FromStr for RomanNumeral {
    type Err = Error;

    fn from_str(s: &str) -> ::std::result::Result<Self, Self::Err> {
        lazy_static! {
            static ref VALUE_REGEX: Regex = Regex::new(
                "^(M*)([DCLXVI]M)?(D*)([CLXVI]D)?(C*)([LXVI]C)?\
                 (L*)([XVI]L)?(X*)([VI]X)?(V*)(IV)?(I*)$"
            )
            .unwrap();
            static ref ADDITIVE_CAPTURE_GROUPS: HashSet<usize> = {
                let mut s: HashSet<usize> = HashSet::new();
                s.insert(1);
                s.insert(3);
                s.insert(5);
                s.insert(7);
                s.insert(9);
                s.insert(11);
                s.insert(13);
                s
            };
            static ref SUBTRACTIVE_CAPTURE_GROUPS: HashSet<usize> = {
                let mut s: HashSet<usize> = HashSet::new();
                s.insert(2);
                s.insert(4);
                s.insert(6);
                s.insert(8);
                s.insert(10);
                s.insert(12);
                s
            };
        }

        let s = s.trim().to_uppercase();
        match VALUE_REGEX.captures(s.as_str()) {
            Some(captures) => {
                // From our regular expression, we have the following capture groups:
                //
                //     i = 1, 3, 5, 7, 9, 11, 13 - Additive groups.
                //     i = 2, 4, 6, 8, 10, 12 - Subtractive groups.
                //
                // Add their values to the running total, checking taht they're value.

                let mut total: i64 = 0;
                for idx in 1..captures.len() {
                    if let Some(capture) = captures.get(idx) {
                        if ADDITIVE_CAPTURE_GROUPS.contains(&idx) {
                            total += get_additive_string_value(capture.as_str())? as i64;
                        } else if SUBTRACTIVE_CAPTURE_GROUPS.contains(&idx) {
                            total += get_subtractive_string_value(capture.as_str())? as i64;
                        } else {
                            bail!("Encountered unexpected capture group index");
                        }
                    }
                }

                if total < 0 {
                    bail!("Roman numerals cannot have negative values");
                }

                Ok(RomanNumeral {
                    value: total as u64,
                })
            }
            None => bail!("Failed to match input string against roman numeral regex"),
        }
    }
}

impl fmt::Display for RomanNumeral {
    fn fmt(&self, f: &mut fmt::Formatter) -> ::std::result::Result<(), fmt::Error> {
        let mut v: u64 = self.value;
        for ov in OUTPUT_VALUES.iter().rev() {
            while v >= ov.value {
                write!(f, "{}", ov.text)?;
                v -= ov.value;
            }
        }
        Ok(())
    }
}
