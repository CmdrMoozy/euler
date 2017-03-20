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

use std::cmp::Ordering;
use std::collections::HashMap;
use std::fmt;
use std::hash::Hash;
use util::error::*;

#[inline]
fn char_at(s: &str, i: usize) -> char { s.chars().nth(i).unwrap() }

#[derive(Clone, Copy, Debug, Eq, Hash, Ord, PartialEq, PartialOrd)]
pub enum Value {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
}

impl Value {
    /// Convert a char to a Value enumeration value. See the function's code
    /// for the mapping.
    pub fn from_char(c: char) -> Result<Value> {
        Ok(match c {
            '2' => Value::Two,
            '3' => Value::Three,
            '4' => Value::Four,
            '5' => Value::Five,
            '6' => Value::Six,
            '7' => Value::Seven,
            '8' => Value::Eight,
            '9' => Value::Nine,
            'T' => Value::Ten,
            'J' => Value::Jack,
            'Q' => Value::Queen,
            'K' => Value::King,
            'A' => Value::Ace,
            _ => bail!("Invalid Value character '{}'", c),
        })
    }
}

impl fmt::Display for Value {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f,
               "{}",
               match *self {
                   Value::Two => '2',
                   Value::Three => '3',
                   Value::Four => '4',
                   Value::Five => '5',
                   Value::Six => '6',
                   Value::Seven => '7',
                   Value::Eight => '8',
                   Value::Nine => '9',
                   Value::Ten => 'T',
                   Value::Jack => 'J',
                   Value::Queen => 'Q',
                   Value::King => 'K',
                   Value::Ace => 'A',
               })
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
pub enum Suit {
    Clubs,
    Diamonds,
    Hearts,
    Spades,
}

impl Suit {
    /// Convert a char to a Suit enumeration value. See the function's code for
    /// the mapping.
    pub fn from_char(c: char) -> Result<Suit> {
        Ok(match c {
            'C' => Suit::Clubs,
            'D' => Suit::Diamonds,
            'H' => Suit::Hearts,
            'S' => Suit::Spades,
            _ => bail!("Invalid Suit character '{}'", c),
        })
    }
}

impl fmt::Display for Suit {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f,
               "{}",
               match *self {
                   Suit::Clubs => 'C',
                   Suit::Diamonds => 'D',
                   Suit::Hearts => 'H',
                   Suit::Spades => 'S',
               })
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Card {
    pub value: Value,
    pub suit: Suit,
}

impl fmt::Display for Card {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}{}", self.value, self.suit)
    }
}

fn to_counts<'a, T: Copy + Eq + Hash, I: Iterator<Item = T>>(items: I) -> HashMap<T, usize> {
    let mut counts: HashMap<T, usize> = HashMap::new();
    for item in items {
        let existing_count: usize = counts.get(&item).cloned().or(Some(0)).unwrap();
        counts.insert(item, existing_count + 1);
    }
    counts
}

fn is_straight(sorted_values: &[Value], value_counts: &HashMap<Value, usize>) -> bool {
    if value_counts.len() != 5 {
        return false;
    }

    let min = sorted_values[4];
    let max = sorted_values[0];

    (min == Value::Two && max == Value::Six) || (min == Value::Three && max == Value::Seven) ||
    (min == Value::Four && max == Value::Eight) || (min == Value::Five && max == Value::Nine) ||
    (min == Value::Six && max == Value::Ten) || (min == Value::Seven && max == Value::Jack) ||
    (min == Value::Eight && max == Value::Queen) ||
    (min == Value::Nine && max == Value::King) || (min == Value::Ten && max == Value::Ace) ||
    (sorted_values == &[Value::Ace, Value::Five, Value::Four, Value::Three, Value::Two])
}

#[derive(Clone, Copy, Debug, Eq, Ord, PartialEq, PartialOrd)]
pub enum Rank {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
}

impl Rank {
    fn rank(sorted_values: &[Value],
            value_counts: &HashMap<Value, usize>,
            suit_counts: &HashMap<Suit, usize>)
            -> Rank {
        let is_flush = suit_counts.len() == 1;
        let is_straight = is_straight(sorted_values, value_counts);

        let mut value_counts_sorted: Vec<usize> = value_counts.values().cloned().collect();
        value_counts_sorted.sort();

        if is_flush && is_straight {
            Rank::StraightFlush
        } else if value_counts.len() == 2 && *value_counts.values().min().unwrap() == 1 {
            Rank::FourOfAKind
        } else if value_counts.len() == 2 && *value_counts.values().min().unwrap() == 2 {
            Rank::FullHouse
        } else if is_flush {
            Rank::Flush
        } else if is_straight {
            Rank::Straight
        } else if value_counts.len() == 3 && value_counts_sorted == vec![1, 1, 3] {
            Rank::ThreeOfAKind
        } else if value_counts.len() == 3 && value_counts_sorted == vec![1, 2, 2] {
            Rank::TwoPair
        } else if value_counts.len() == 4 {
            Rank::OnePair
        } else {
            Rank::HighCard
        }
    }
}

fn get_rank_value_counts(rank: Rank,
                         value_counts: &HashMap<Value, usize>)
                         -> HashMap<Value, usize> {
    match rank {
        Rank::StraightFlush => value_counts.clone(),
        Rank::FourOfAKind => value_counts.clone().into_iter().filter(|pair| pair.1 == 4).collect(),
        Rank::FullHouse => value_counts.clone(),
        Rank::Flush => value_counts.clone(),
        Rank::Straight => value_counts.clone(),
        Rank::ThreeOfAKind => value_counts.clone().into_iter().filter(|pair| pair.1 == 3).collect(),
        Rank::TwoPair => value_counts.clone().into_iter().filter(|pair| pair.1 == 2).collect(),
        Rank::OnePair => value_counts.clone().into_iter().filter(|pair| pair.1 == 2).collect(),
        Rank::HighCard => {
            let mut rvc = HashMap::new();
            let value = value_counts.iter().map(|pair| *pair.0).max().unwrap();
            rvc.insert(value, 1);
            rvc
        },
    }
}

fn get_other_value_counts(value_counts: &HashMap<Value, usize>,
                          rank_value_counts: &HashMap<Value, usize>)
                          -> HashMap<Value, usize> {
    let mut ovc = value_counts.clone();
    for (value, count) in rank_value_counts {
        *ovc.get_mut(&value).unwrap() -= *count;
        if ovc[value] == 0 {
            ovc.remove(&value);
        }
    }
    ovc
}

// A hand description looks like "VS VS VS VS VS" where V is a value and S is a
// suit. So the length of a valid description is 5 sets of 2 characters, plus 4
// spaces.
const HAND_DESC_LENGTH: usize = 2 * 5 + 4;

#[derive(Clone, Debug)]
pub struct Hand {
    cards: [Card; 5],
    sorted_values: Vec<Value>,
    value_counts: HashMap<Value, usize>,
    suit_counts: HashMap<Suit, usize>,
    rank: Rank,
    rank_value_counts: HashMap<Value, usize>,
    other_value_counts: HashMap<Value, usize>,
}

impl Hand {
    fn new(cards: [Card; 5]) -> Hand {
        let mut values: Vec<Value> = cards.iter().map(|c| c.value).collect();
        values.sort_by(|a, b| b.cmp(a));
        let value_counts: HashMap<Value, usize> = to_counts(cards.iter().map(|c| c.value));
        let suit_counts = to_counts(cards.iter().map(|c| c.suit));
        let rank = Rank::rank(values.as_slice(), &value_counts, &suit_counts);
        let rank_value_counts = get_rank_value_counts(rank, &value_counts);
        let other_value_counts = get_other_value_counts(&value_counts, &rank_value_counts);
        Hand {
            cards: cards,
            sorted_values: values,
            value_counts: value_counts,
            suit_counts: suit_counts,
            rank: rank,
            rank_value_counts: rank_value_counts,
            other_value_counts: other_value_counts,
        }
    }

    /// This function parses a Hand from the given string. The string must be
    /// formatted as "VS VS VS VS VS", where each 'V' represents the card
    /// value, and 'S' represents the card suit. See `Value::from_char` and
    /// `Suit::from_char` for details.
    pub fn parse_hand(s: &str) -> Result<Hand> {
        if s.len() != HAND_DESC_LENGTH {
            bail!("Invalid hand description '{}'", s);
        }

        Ok(Self::new([Card {
                          value: try!(Value::from_char(char_at(s, 0))),
                          suit: try!(Suit::from_char(char_at(s, 1))),
                      },
                      Card {
                          value: try!(Value::from_char(char_at(s, 3))),
                          suit: try!(Suit::from_char(char_at(s, 4))),
                      },
                      Card {
                          value: try!(Value::from_char(char_at(s, 6))),
                          suit: try!(Suit::from_char(char_at(s, 7))),
                      },
                      Card {
                          value: try!(Value::from_char(char_at(s, 9))),
                          suit: try!(Suit::from_char(char_at(s, 10))),
                      },
                      Card {
                          value: try!(Value::from_char(char_at(s, 12))),
                          suit: try!(Suit::from_char(char_at(s, 13))),
                      }]))
    }

    /// This is a convenience function which parses a pair of two hands,
    /// formatted like: "HAND HAND" where each "HAND" is a hand formatted as
    /// per `parse_hand`. See that other function for more details.
    pub fn parse_two_hands(s: &str) -> Result<(Hand, Hand)> {
        if s.len() != 2 * HAND_DESC_LENGTH + 1 {
            bail!("Invalid hand pair description '{}'", s);
        }
        Ok((try!(Self::parse_hand(&s[0..HAND_DESC_LENGTH])),
            try!(Self::parse_hand(&s[HAND_DESC_LENGTH + 1..]))))
    }

    pub fn get_rank(&self) -> Rank { self.rank }

    fn is_steel_wheel(&self) -> bool {
        (self.rank == Rank::Straight || self.rank == Rank::StraightFlush) &&
        self.sorted_values[4] == Value::Two && self.sorted_values[0] == Value::Ace
    }
}

impl PartialEq for Hand {
    fn eq(&self, other: &Hand) -> bool { self.cmp(other) == Ordering::Equal }
}

impl Eq for Hand {}

impl PartialOrd for Hand {
    fn partial_cmp(&self, other: &Hand) -> Option<Ordering> { Some(self.cmp(other)) }
}

impl Ord for Hand {
    fn cmp(&self, other: &Hand) -> Ordering {
        let rank_ordering = self.rank.cmp(&other.rank);
        if rank_ordering != Ordering::Equal {
            return rank_ordering;
        }

        if self.rank == Rank::HighCard || self.rank == Rank::Flush {
            return self.sorted_values.cmp(&other.sorted_values);
        } else if self.rank == Rank::Straight || self.rank == Rank::StraightFlush {
            return if self.is_steel_wheel() && other.is_steel_wheel() {
                Ordering::Equal
            } else if self.is_steel_wheel() {
                Ordering::Less
            } else if other.is_steel_wheel() {
                Ordering::Greater
            } else {
                self.sorted_values.cmp(&other.sorted_values)
            };
        } else if self.rank == Rank::OnePair || self.rank == Rank::TwoPair ||
                  self.rank == Rank::ThreeOfAKind ||
                  self.rank == Rank::FourOfAKind {
            let mut a_rank_values: Vec<Value> = self.rank_value_counts.keys().cloned().collect();
            a_rank_values.sort_by(|a, b| b.cmp(a));
            let mut b_rank_values: Vec<Value> = other.rank_value_counts.keys().cloned().collect();
            b_rank_values.sort_by(|a, b| b.cmp(a));
            let ordering = a_rank_values.cmp(&b_rank_values);
            if ordering != Ordering::Equal {
                return ordering;
            }

            let mut a_other_values: Vec<Value> = self.other_value_counts.keys().cloned().collect();
            a_other_values.sort_by(|a, b| b.cmp(a));
            let mut b_other_values: Vec<Value> = other.other_value_counts.keys().cloned().collect();
            b_other_values.sort_by(|a, b| b.cmp(a));
            return a_other_values.cmp(&b_other_values);
        } else if self.rank == Rank::FullHouse {
            let a_three_value =
                self.rank_value_counts.iter().filter(|pair| *pair.1 == 3).next().unwrap().0;
            let b_three_value =
                other.rank_value_counts.iter().filter(|pair| *pair.1 == 3).next().unwrap().0;
            let ordering = a_three_value.cmp(&b_three_value);
            if ordering != Ordering::Equal {
                return ordering;
            }

            let a_two_value =
                self.rank_value_counts.iter().filter(|pair| *pair.1 == 2).next().unwrap().0;
            let b_two_value =
                other.rank_value_counts.iter().filter(|pair| *pair.1 == 2).next().unwrap().0;
            return a_two_value.cmp(&b_two_value);
        }

        unreachable!();
    }
}

impl fmt::Display for Hand {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f,
               "{} {} {} {} {}",
               self.cards[0],
               self.cards[1],
               self.cards[2],
               self.cards[3],
               self.cards[4])
    }
}
