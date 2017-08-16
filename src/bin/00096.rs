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

// Su Doku (Japanese meaning number place) is the name given to a popular
// puzzle concept. Its origin is unclear, but credit must be attributed to
// Leonhard Euler who invented a similar, and much more difficult, puzzle idea
// called Latin Squares. The objective of Su Doku puzzles, however, is to
// replace the blanks (or zeros) in a 9 by 9 grid such that each row, column,
// and 3 by 3 box contains each of the digits 1 to 9. Below is an example of a
// typical starting puzzle grid and its solution grid.
//
//     |-------|-------|-------|    |-------|-------|-------|
//     | 0 0 3 | 0 2 0 | 6 0 0 |    | 4 8 3 | 9 2 1 | 6 5 7 |
//     | 9 0 0 | 3 0 5 | 0 0 1 |    | 9 6 7 | 3 4 5 | 8 2 1 |
//     | 0 0 1 | 8 0 6 | 4 0 0 |    | 2 5 1 | 8 7 6 | 4 9 3 |
//     |-------|-------|-------|    |-------|-------|-------|
//     | 0 0 8 | 1 0 2 | 9 0 0 |    | 5 4 8 | 1 3 2 | 9 7 6 |
//     | 7 0 0 | 0 0 0 | 0 0 8 |    | 7 2 9 | 5 6 4 | 1 3 8 |
//     | 0 0 6 | 7 0 8 | 2 0 0 |    | 1 3 6 | 7 9 8 | 2 4 5 |
//     |-------|-------|-------|    |-------|-------|-------|
//     | 0 0 2 | 6 0 9 | 5 0 0 |    | 3 7 2 | 6 8 9 | 5 1 4 |
//     | 8 0 0 | 2 0 3 | 0 0 9 |    | 8 1 4 | 2 5 3 | 7 6 9 |
//     | 0 0 5 | 0 1 0 | 3 0 0 |    | 6 9 5 | 4 1 7 | 3 8 2 |
//     |-------|-------|-------|    |-------|-------|-------|
//
// A well constructed Su Doku puzzle has a unique solution and can be solved by
// logic, although it may be necessary to employ "guess and test" methods in
// order to eliminate options (there is much contested opinion over this). The
// complexity of the search determines the difficulty of the puzzle; the
// example above is considered easy because it can be solved by straight
// forward direct deduction.
//
// The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'),
// contains fifty different Su Doku puzzles ranging in difficulty, but all with
// unique solutions (the first puzzle in the file is the example above).
//
// By solving all fifty puzzles find the sum of the 3-digit numbers found in
// the top left corner of each solution grid; for example, 483 is the 3-digit
// number found in the top left corner of the solution grid above.

extern crate euler;
use self::euler::dsc::sudoku::Puzzle;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const INPUT_PUZZLES: &'static str = include_str!("00096.txt");

const EXPECTED_RESULT: u64 = 24702;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let puzzles = Puzzle::from_text(INPUT_PUZZLES)?;

        Ok(ProblemAnswer {
            actual: 0,
            expected: EXPECTED_RESULT,
        })
    });
}

/*
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <thread>
#include <vector>

#include "common/euler/ESudoku.h"
#include "common/util/Path.hpp"
#include "common/util/Process.hpp"

 * This structure defines the context of a consumer thread, including our list
 * of puzzles that are to be solved, the total from the solved puzzles, and an
 * error flag for consumers to indicate failure.
typedef struct ThreadContext
{
	std::vector<std::vector<int>> puzzles;
	std::atomic<std::size_t> next;
	std::atomic<int> total;

	bool error;

} ThreadContext;

 * Consumers take unsolved puzzles, solve them, and then add the resulting
 * answer to our context.
void solvePuzzles(ThreadContext &context)
{
	ESudoku solver;
	int a;
	std::vector<int> puzzle;

	// Keep going until the loop terminates itself.

	while(true)
	{
		// Get the next puzzle and increment the index.
		std::size_t p =
		        context.next.fetch_add(1, std::memory_order_seq_cst);
		if(static_cast<std::size_t>(p) >= context.puzzles.size())
			break;

		// Try to solve the puzzle.

		if(!solver.load(context.puzzles.at(p)))
		{
			std::cout << "Failed to load puzzle!\n";
			context.error = true;
			return;
		}

		if(!solver.solve(true))
		{
			std::cout << "Failed to solve puzzle!\n";
			context.error = true;
			return;
		}

		puzzle = solver.getSolution();

		a = puzzle[0];
		a *= 10;
		a += puzzle[1];
		a *= 10;
		a += puzzle[2];

		// Add our solution to the total.
		context.total.fetch_add(a, std::memory_order_seq_cst);
	}
}

euler::util::process::ProblemResult<int> problem()
{
	std::vector<int> puzzle;

	// Initialize thread context.

	ThreadContext context;
	context.next = 0;
	context.total = 0;
	context.error = false;

	// Spin up some threads to solve the puzzles.
	std::vector<std::shared_ptr<std::thread>> threads;
	for(unsigned i = 0; i < std::thread::hardware_concurrency(); ++i)
	{
		auto work = [&context]() { solvePuzzles(context); };
		threads.push_back(std::make_shared<std::thread>(work));
	}

	// Wait for the threads to finish up.
	for(auto thread : threads)
	{
		try
		{
			thread->join();
		}
		catch(const std::system_error &e)
		{
			if(e.code() != std::errc::invalid_argument)
				throw;
		}
	}
	threads.clear();

	// Print the answer!

	if(!context.error)
	{
		return {context.total.load(std::memory_order_seq_cst),
		        EXPECTED_RESULT};
	}
	else
	{
		throw std::runtime_error(
		        "One or more threads did not complete successfully!");
	}
}
*/
