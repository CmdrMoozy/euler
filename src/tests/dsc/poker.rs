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

use dsc::poker::*;
use std::cmp::Ordering;

#[test]
fn test_rank_ordering() {
    assert!(Rank::StraightFlush > Rank::FourOfAKind);
    assert!(Rank::FourOfAKind > Rank::FullHouse);
    assert!(Rank::FullHouse > Rank::Flush);
    assert!(Rank::Flush > Rank::Straight);
    assert!(Rank::Straight > Rank::ThreeOfAKind);
    assert!(Rank::ThreeOfAKind > Rank::TwoPair);
    assert!(Rank::TwoPair > Rank::OnePair);
    assert!(Rank::OnePair > Rank::HighCard);
}

#[test]
fn test_poker_hand_ranking() {
    static TEST_CASES: &'static [(&'static str, Rank)] = &[("AD 2D 3D 4D 5D", Rank::StraightFlush),
                                                           ("6H 7H 8H 9H TH", Rank::StraightFlush),
                                                           ("2D 2D 2D 2D 3D", Rank::FourOfAKind),
                                                           ("2D 2D 2D 3D 3D", Rank::FullHouse),
                                                           ("2D 2D 2D 3D 4D", Rank::Flush),
                                                           ("AD 2C 3C 4C 5C", Rank::Straight),
                                                           ("6H 7C 8C 9D TD", Rank::Straight),
                                                           ("2D 2D 2D 3C 4H", Rank::ThreeOfAKind),
                                                           ("8D 8D 7C 7C 6H", Rank::TwoPair),
                                                           ("8D 8D 5C 6C 7C", Rank::OnePair),
                                                           ("AD 2S 5C 7H 8H", Rank::HighCard),
                                                           ("8C TS KC 9H 4S", Rank::HighCard),
                                                           ("7D 2S 5S 3S AC", Rank::HighCard),
                                                           ("QC KC AC 2C 3C", Rank::Flush),
                                                           ("6D 7C 5D 5H 3S", Rank::OnePair),
                                                           ("5C JC 2H 5S 3D", Rank::OnePair)];

    for test_case in TEST_CASES {
        let hand = Hand::parse_hand(test_case.0).unwrap();
        assert!(hand.get_rank() == test_case.1,
                "Assertion failed: rank({}) == {:?} (got {:?})",
                hand,
                test_case.1,
                hand.get_rank());
    }
}

#[test]
fn test_poker_hand_comparison() {
    static TEST_CASES: &'static [(&'static str, Ordering)] =
        &[// Pair of 5's vs pair of 8's
          ("5H 5C 6S 7S KD 2C 3S 8S 8D TD", Ordering::Less),
          // A-high vs Q-high
          ("5D 8C 9S JS AC 2C 5C 7D 8S QH", Ordering::Greater),
          // Three A's vs Diamond flush
          ("2D 9C AS AH AC 3D 6D 7D QD QD", Ordering::Less),
          // Pair of Q's, 9-high vs Pair of Q's, 7-high
          ("4D 6S 9H QH QC 3D 6D 7H QD QS", Ordering::Greater),
          // Full house, 3 4's vs full house, 3 3's
          ("2H 2D 4C 4D 4S 3C 3D 3S 9S 9D", Ordering::Greater),
          // Full house, 2 2's vs full house, 2 3's
          ("2H 2D 4C 4D 4S 3C 3D 4S 4S 4D", Ordering::Less),
          // Three 2's, 4-high vs three 2's, 3-high
          ("2H 2H 2H 4D KD 2S 2S 2S KS 3H", Ordering::Greater),
          // Two steel wheels, different suits
          ("AH 2D 3D 4D 5D AC 2S 3S 4S 5S", Ordering::Equal),
          // Steel wheel vs straight
          ("AH 2D 3D 4D 5D 2C 3S 4S 5S 6S", Ordering::Less),
          // Straight vs steel wheel
          ("2H 3D 4D 5D 6D AC 2S 3S 4S 5S", Ordering::Greater),
          // Straight, 7-high vs straight, 8-high
          ("3H 4D 5D 6D 7D 4C 5S 6S 7S 8S", Ordering::Less),
          // Flush, K-high vs flush, A-high
          ("3H 7H 9H JH KH 9C 6C 7C 8C AC", Ordering::Less),
          // Royal flush vs flush, K-high
          ("TH JH QH KH AH 9C TC JC QC KC", Ordering::Greater),
          // Royal flush vs steel wheel
          ("TH JH QH KH AH AC 2C 3C 4C 5C", Ordering::Greater),
          // K-high vs A-high (regression)
          ("8C TS KC 9H 4S 7D 2S 5D 3S AC", Ordering::Less),
          // Pair of 5's, 7-high vs pair of 5's, J-high (regression)
          ("6D 7C 5D 5H 3S 5C JC 2H 5S 3D", Ordering::Less)];

    for test_case in TEST_CASES {
        let (a, b) = Hand::parse_two_hands(test_case.0).unwrap();
        assert!(a.cmp(&b) == test_case.1,
                "Assertion failed: {} {} {}",
                a,
                match test_case.1 {
                    Ordering::Less => "<",
                    Ordering::Equal => "==",
                    Ordering::Greater => ">",
                },
                b);
    }
}
