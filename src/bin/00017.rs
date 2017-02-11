// euler - A collection of ProjectEuler libraries, tools, and solutions.
// Copyright (C) 2013 Axel Rasmussen
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// If the numbers 1 to 5 are written out in words: one, two, three, four, five,
// then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
//
// If all the numbers from 1 to 1000 (one thousand) inclusive were written out
// in words, how many letters would be used?
//
// NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
// forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
// letters. The use of "and" when writing out numbers is in compliance with
// British usage.

use std::collections::HashMap;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

#[macro_use]
extern crate lazy_static;

lazy_static! {
/// A mapping from single digits to their spelled-out names.
    static ref LITERAL_DIGITS: HashMap<u64, &'static str> = {
        let mut m = HashMap::new();
        m.insert(0, "Zero");
        m.insert(1, "One");
        m.insert(2, "Two");
        m.insert(3, "Three");
        m.insert(4, "Four");
        m.insert(5, "Five");
        m.insert(6, "Six");
        m.insert(7, "Seven");
        m.insert(8, "Eight");
        m.insert(9, "Nine");
        m
    };

    /// A mapping from the second digit of a "special" (teens, for example) value to the
    /// value's spelled-out name.
    static ref LITERAL_SPECIAL: HashMap<u64, &'static str> = {
        let mut m = HashMap::new();
        m.insert(1, "Eleven");
        m.insert(2, "Twelve");
        m.insert(3, "Thirteen");
        m.insert(4, "Fourteen");
        m.insert(5, "Fifteen");
        m.insert(6, "Sixteen");
        m.insert(7, "Seventeen");
        m.insert(8, "Eighteen");
        m.insert(9, "Nineteen");
        m
    };

    /// A mapping from the first digit of a multiple of ten (e.g., for "10" the key in the
    /// map is '1') to this value's spelled-out name.
    static ref LITERAL_TEN_MULTIPLES: HashMap<u64, &'static str> = {
        let mut m = HashMap::new();
        m.insert(1, "Ten");
        m.insert(2, "Twenty");
        m.insert(3, "Thirty");
        m.insert(4, "Forty");
        m.insert(5, "Fifty");
        m.insert(6, "Sixty");
        m.insert(7, "Seventy");
        m.insert(8, "Eighty");
        m.insert(9, "Ninety");
        m
    };

    // LITERAL_PLACES
    /// A mapping from the exponent on a power of ten to that power-of-ten's spelled-out name.
    static ref LITERAL_POWERS_OF_TEN: HashMap<u64, &'static str> = {
        let mut m = HashMap::new();
        m.insert(3, "Hundred");
        m.insert(4, "Thousand");
        m.insert(6, "Million");
        m.insert(9, "Billion");
        m
    };
}

const EXPECTED_RESULT: usize = 21124;

/// This function will spell-out an input number -- i.e., "123" becomes "one
/// hundred and twenty-three".
///
/// This function can only handle numbers up to the billions, so your input
/// number must be <= 9,999,999,999 or the result is undefined.
fn number_to_literal(n: u64) -> String {
    let digits: Vec<u64> =
        n.to_string().chars().map(|c| c.to_string().parse::<u64>().unwrap()).rev().collect();
    let mut result = String::new();

    // Loop through each digit in the number, in reverse.
    let mut idx_iter = (0..digits.len()).rev();
    while let Some(idx) = idx_iter.next() {
        let digit: u64 = digits[idx];
        let place: u64 = idx as u64 + 1;

        match place {
            10 => {
                result.push_str(format!("{} {} ",
                                        LITERAL_DIGITS.get(&digit).unwrap(),
                                        LITERAL_POWERS_OF_TEN.get(&(place - 1)).unwrap())
                    .as_str());
            },
            9 => {
                if digit > 0 {
                    result.push_str(format!("{} {} ",
                                            LITERAL_DIGITS.get(&digit).unwrap(),
                                            LITERAL_POWERS_OF_TEN.get(&3).unwrap())
                        .as_str());
                    if digits[idx - 2] > 0 || digits[idx - 1] > 0 {
                        result.push_str("and ");
                    }
                }
            },
            8 => {
                if digit == 1 {
                    if digits[idx - 1] > 0 {
                        result.push_str(format!("{} {} ",
                                                LITERAL_SPECIAL.get(&digits[idx - 1]).unwrap(),
                                                LITERAL_POWERS_OF_TEN.get(&(place - 1)).unwrap())
                            .as_str());
                        idx_iter.next().unwrap();
                    }
                } else if digit > 1 {
                    result.push_str(LITERAL_TEN_MULTIPLES.get(&digit).unwrap());

                    if digits[idx - 1] > 0 {
                        result.push_str("-");
                    } else {
                        result.push_str(format!(" {} ",
                                                LITERAL_POWERS_OF_TEN.get(&(place - 1)).unwrap())
                            .as_str());
                        idx_iter.next().unwrap();
                    }
                }
            },
            7 => {
                if digit > 0 {
                    result.push_str(format!("{} ", LITERAL_DIGITS.get(&digit).unwrap()).as_str());
                }
                result.push_str(format!("{} ", LITERAL_POWERS_OF_TEN.get(&(place - 1)).unwrap())
                    .as_str());
            },
            6 => {
                if digit > 0 {
                    result.push_str(format!("{} {} ",
                                            LITERAL_DIGITS.get(&digit).unwrap(),
                                            LITERAL_POWERS_OF_TEN.get(&3).unwrap())
                        .as_str());
                    if digits[idx - 2] > 0 || digits[idx - 1] > 0 {
                        result.push_str("and ");
                    }
                }
            },
            5 => {
                if digit == 1 {
                    if digits[idx - 1] > 0 {
                        result.push_str(format!("{} {} ",
                                                LITERAL_SPECIAL.get(&digits[idx - 1]).unwrap(),
                                                LITERAL_POWERS_OF_TEN.get(&(place - 1)).unwrap())
                            .as_str());
                        idx_iter.next().unwrap();
                    }
                } else if digit > 1 {
                    result.push_str(LITERAL_TEN_MULTIPLES.get(&digit).unwrap());
                    if digits[idx - 1] > 0 {
                        result.push_str("-");
                    } else {
                        result.push_str(format!(" {} ",
                                                LITERAL_POWERS_OF_TEN.get(&(place - 1)).unwrap())
                            .as_str());
                        idx_iter.next().unwrap();
                    }
                }
            },
            4 => {
                if digit > 0 {
                    result.push_str(format!("{} ", LITERAL_DIGITS.get(&digit).unwrap()).as_str());
                }
                result.push_str(format!("{} ",
                                        LITERAL_POWERS_OF_TEN.get(&place).unwrap()).as_str());
            },
            3 => {
                if digit > 0 {
                    result.push_str(format!("{} {} ",
                                            LITERAL_DIGITS.get(&digit).unwrap(),
                                            LITERAL_POWERS_OF_TEN.get(&3).unwrap())
                        .as_str());
                    if digits[idx - 2] > 0 || digits[idx - 1] > 0 {
                        result.push_str("and ");
                    }
                }
            },
            2 => {
                if digit == 1 {
                    if digits[idx - 1] > 0 {
                        result.push_str(format!("{} ",
                                                LITERAL_SPECIAL.get(&digits[idx - 1]).unwrap())
                            .as_str());
                    } else {
                        result.push_str(format!("{} ", LITERAL_TEN_MULTIPLES.get(&1).unwrap())
                            .as_str());
                    }
                    idx_iter.next().unwrap();
                } else if digit > 1 {
                    result.push_str(LITERAL_TEN_MULTIPLES.get(&digit).unwrap());
                    if digits[idx - 1] > 0 {
                        result.push_str("-");
                    } else {
                        result.push_str(" ");
                        idx_iter.next().unwrap();
                    }
                }
            },
            1 => {
                if digit > 0 {
                    result.push_str(format!("{} ", LITERAL_DIGITS.get(&digit).unwrap()).as_str());
                }
            },
            _ => panic!("Attempted to convert an unsupported number to a literal."),
        };
    }

    result
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut count: usize = 0;
        for n in 1..1001 {
            let literal = number_to_literal(n);
            count += literal.chars().filter(|c| !c.is_whitespace()).filter(|c| *c != '-').count();
        }

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}
