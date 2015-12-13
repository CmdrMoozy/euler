/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
#include "common/util/Process.hpp"

namespace
{
constexpr int EXPECTED_RESULT = 24702;

/*
 * This structure defines the context of a consumer thread, including our list
 * of puzzles that are to be solved, the total from the solved puzzles, and an
 * error flag for consumers to indicate failure.
 */
typedef struct ThreadContext
{
	std::vector<std::vector<int>> puzzles;
	std::atomic<std::size_t> next;
	std::atomic<int> total;

	bool error;

} ThreadContext;

/*
 * Consumers take unsolved puzzles, solve them, and then add the resulting
 * answer to our context.
 */
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

	// Read the puzzles from the input file, sudoku.txt

	std::string line;
	char *buf = new char[2];
	std::ifstream pfile("sudoku.txt");

	if(!pfile.is_open())
	{
		throw std::runtime_error(
		        "Failed to open input file 'sudoku.txt'!");
	}

	buf[1] = '\0';

	while(pfile.good())
	{
		std::getline(pfile, line);

		if((line[0] == 'G') && (line[1] == 'r') && (line[2] == 'i') &&
		   (line[3] == 'd'))
		{ // If this line is specifying "Grid ##"...

			// Insert the previous puzzle, if any.
			if(puzzle.size() == 81)
				context.puzzles.push_back(puzzle);
			puzzle.clear();
		}
		else
		{ // Otherwise, grab numbers from it!

			for(unsigned int i = 0; i < line.size(); ++i)
			{
				if(isdigit(line[i]))
				{
					buf[0] = line[i];
					puzzle.push_back(atoi(buf));
				}
			}
		}
	}

	// Push the final puzzle.
	if(puzzle.size() == 81)
		context.puzzles.push_back(puzzle);

	// Clean up our input buffer and file object.
	delete[] buf;
	pfile.close();

	// Spin up some threads to solve the puzzles.
	std::vector<std::shared_ptr<std::thread>> threads;
	for(unsigned i = 0; i < std::thread::hardware_concurrency(); ++i)
	{
		auto work = [&context]()
		{
			solvePuzzles(context);
		};
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
}

EULER_PROBLEM_ENTRYPOINT
