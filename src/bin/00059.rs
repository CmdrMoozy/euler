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

// Each character on a computer is assigned a unique code and the preferred
// standard is ASCII (American Standard Code for Information Exchange). For
// example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.
//
// A modern encryption method is to take a text file, convert the bytes to
// ASCII, then XOR each byte with a given value, taken from a secret key. The
// advantage with the XOR function is that using the same encryption key on the
// cipher text, restores the plain text; for example, 65 XOR 42 = 107, then 107
// XOR 42 = 65.
//
// For unbreakable encryption, the key is the same length as the plain text
// message, and the key is made up of random bytes. The user would keep the
// encrypted message and the encryption key in different locations, and without
// both "halves", it is impossible to decrypt the message.
//
// Unfortunately, this method is impractical for most users, so the modified
// method is to use a password as a key. If the password is shorter than the
// message, which is likely, the key is repeated cyclically throughout the
// message. The balance for this method is using a sufficiently long password
// key for security, but short enough to be memorable.
//
// Your task has been made easy, as the encryption key consists of three lower
// case characters. Using cipher.txt (right click and 'Save Link/Target
// As...'), a file containing the encrypted ASCII codes, and the knowledge that
// the plain text must contain common English words, decrypt the message and
// find the sum of the ASCII values in the original text.

#[macro_use]
extern crate error_chain;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

static CIPHERTEXT: &'static str = include_str!("00059.txt");

static PUNCTUATION: &'static [char] = &['\'', '"', '.', ',', ':', ';', '(', ')', '!', '?'];
static ENCRYPTION_KEYSPACE: &'static [char] = &['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                                                'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                                                'u', 'v', 'w', 'x', 'y', 'z'];

const EXPECTED_RESULT: u64 = 107359;

#[inline]
fn is_punctuation(c: char) -> bool { PUNCTUATION.contains(&c) }

fn is_valid_decrypted_char(c: char) -> bool {
    c.is_alphabetic() || c.is_numeric() || c.is_whitespace() || is_punctuation(c)
}

fn char_to_byte(c: char) -> Result<u8> {
    let bytes = c as u32;
    if bytes > std::u8::MAX as u32 {
        bail!("Converting char to byte failed, as char contains more than one byte");
    }
    Ok(bytes as u8)
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let ciphertext: Vec<u8> =
            CIPHERTEXT.split(',').map(|b| b.trim().parse::<u8>().unwrap()).collect();
        let mut result: Option<u64> = None;

        for key_a in ENCRYPTION_KEYSPACE.iter() {
            for key_b in ENCRYPTION_KEYSPACE.iter() {
                for key_c in ENCRYPTION_KEYSPACE.iter() {
                    let key = vec![key_a, key_b, key_c];
                    let plaintext: Result<Vec<char>> = ciphertext.iter()
                        .enumerate()
                        .map(|pair| {
                            let k = char_to_byte(*key[pair.0 % key.len()]).unwrap();
                            let b = *pair.1 ^ k;
                            let c = char::from(b);
                            if !is_valid_decrypted_char(c) {
                                bail!("Invalid decryption key");
                            }
                            Ok(c)
                        })
                        .collect();

                    if let Ok(plaintext) = plaintext {
                        let r: Result<u64> = plaintext.iter().fold(Ok(0_u64), |acc, c| {
                            Ok(try!(acc) + try!(char_to_byte(*c)) as u64)
                        });
                        result = Some(try!(r));
                        break;
                    }
                }

                if result.is_some() {
                    break;
                }
            }

            if result.is_some() {
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: result.unwrap(),
            expected: EXPECTED_RESULT,
        })
    });
}
