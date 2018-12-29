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

// In the card game poker, a hand consists of five cards and are ranked, from
// lowest to highest, in the following way:
//
//     High Card: Highest value card.
//     One Pair: Two cards of the same value.
//     Two Pairs: Two different pairs.
//     Three of a Kind: Three cards of the same value.
//     Straight: All cards are consecutive values.
//     Flush: All cards of the same suit.
//     Full House: Three of a kind and a pair.
//     Four of a Kind: Four cards of the same value.
//     Straight Flush: All cards are consecutive values of same suit.
//     Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
//
// The cards are valued in the order:
// 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
//
// If two players have the same ranked hands then the rank made up of the
// highest value wins; for example, a pair of eights beats a pair of fives (see
// example 1 below). But if two ranks tie, for example, both players have a
// pair of queens, then highest cards in each hand are compared (see example 4
// below); if the highest cards tie then the next highest cards are compared,
// and so on.
//
// Consider the following five hands dealt to two players:
//
// Hand     Player 1          Player 2        Winner
//  1    5H 5C 6S 7S KD    2C 3S 8S 8D TD    Player 2
//       Pair of Fives     Pair of Eights
//
//  2    5D 8C 9S JS AC    2C 5C 7D 8S QH    Player 1
//       Highest card A    Highest card Q
//
//  3    2D 9C AS AH AC    3D 6D 7D TD QD    Player 2
//       Three Aces        Flush with Ds
//
//  4    4D 6S 9H QH QC    3D 6D 7H QD QS    Player 1
//       Pair of Queens    Pair of Queens
//       Highest card 9    Highest card 7
//
//  5    2H 2D 4C 4D 4S    3C 3D 3S 9S 9D    Player 1
//       Full House        Full House
//       With Three 4s     With Three 3s
//
// The file, poker.txt, contains one-thousand random hands dealt to two
// players. Each line of the file contains ten cards (separated by a single
// space): the first five are Player 1's cards and the last five are Player 2's
// cards. You can assume that all hands are valid (no invalid characters or
// repeated cards), each player's hand is in no specific order, and in each
// hand there is a clear winner.
//
// How many hands does Player 1 win?

use euler::dsc::poker::*;
use euler::util::error::*;
use euler::util::problem::*;

const HANDS: &'static str = include_str!("00054.txt");

const EXPECTED_RESULT: usize = 376;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let hands: Result<Vec<(Hand, Hand)>> = HANDS
            .lines()
            .map(|line| Hand::parse_two_hands(line))
            .collect();
        Ok(ProblemAnswer {
            actual: hands?
                .iter()
                .map(|hand_pair| hand_pair.0 > hand_pair.1)
                .fold(0_usize, |acc, won| match won {
                    false => acc,
                    true => acc + 1,
                }),
            expected: EXPECTED_RESULT,
        })
    });
}
