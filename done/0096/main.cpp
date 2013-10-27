#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>

extern "C"
{
	#include <pthread.h>
	#include <unistd.h>
}

#include "libeuler/euler/ESudoku.h"

// Utilize (# processors) + 1 threads.
#define THREADS
#define CONSUMER_THREAD_COUNT ( ((int) sysconf(_SC_NPROCESSORS_ONLN)) + 1 )

/*
 * This structure defines the context of a consumer thread, including our list of puzzles that
 * are to be solved, the total from the solved puzzles, a mutex consumers can lock so they can
 * pop puzzles off the list or add to the total, and an error flag for consumers to indicate
 * failure.
 */
typedef struct ThreadContext
{
	
	std::vector< std::vector<int> > puzzles;
	int next;
	int total;
	
	bool error;
	
} ThreadContext;

/*
 * Consumers take unsolved puzzles, solve them, and then add the resulting answer to our context.
 */
void *consumer(void *c)
{
	ESudoku solver;
	int a;
	ThreadContext *context = (ThreadContext *) c;
	std::vector<int> puzzle;
	
	// Keep going until the loop terminates itself.
	
	while(true)
	{
		// Get the next puzzle and increment the index.
		
		int p = __sync_fetch_and_add(&context->next, 1); // Atomic fetch & inc ftw - no locking needed.
		if(static_cast<size_t>(p) >= context->puzzles.size()) break;
		
		// Try to solve the puzzle.
		
		if(!solver.load(context->puzzles.at(p)))
		{
			std::cout << "Failed to load puzzle!\n";
			context->error = true;
			return NULL;
		}
		
		if(!solver.solve(true))
		{
			std::cout << "Failed to solve puzzle!\n";
			context->error = true;
			return NULL;
		}
		
		puzzle = solver.getSolution();
		
		a = puzzle[0];
		a *= 10;
		a += puzzle[1];
		a *= 10;
		a += puzzle[2];
		
		// Add our solution to the total (use GCC atomic add so we don't need to wait for lock).
		
		__sync_fetch_and_add(&context->total, a);
	}
	
	return NULL;
}

/*
 * main() parses our sudoku input file and then starts worker threads to 
 */
int main(void)
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
		std::cout << "Failed to open input file 'sudoku.txt'!\n";
		return 1;
	}
	
	buf[1] = '\0';
	
	while(pfile.good())
	{
		std::getline(pfile, line);
		
		if( (line[0] == 'G') && (line[1] == 'r') && (line[2] == 'i') && (line[3] == 'd') )
		{ // If this line is specifying "Grid ##"...
			
			// Insert the previous puzzle, if any.
			if(puzzle.size() == 81) context.puzzles.push_back(puzzle);
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
	if(puzzle.size() == 81) context.puzzles.push_back(puzzle);
	
	// Clean up our input buffer and file object.
	delete[] buf;
	pfile.close();
	
	#ifdef THREADS
		
		// Spin up some threads to solve the puzzles.
		
		pthread_t threads[CONSUMER_THREAD_COUNT];
		int rc;
		
		for(int i = 0; i < CONSUMER_THREAD_COUNT; ++i)
		{
			rc = pthread_create(&threads[i], NULL, consumer, (void *) &context);
			if(rc)
			{
				std::cout << "Unable to start thread!\n";
				return 1;
			}
		}
		
		// Wait for threads to finish up.
		
		for(int i = 0; i < CONSUMER_THREAD_COUNT; ++i)
			pthread_join(threads[i], NULL);
		
		// Print the answer!
		
		if(!context.error)
		{
			std::cout << "The sum of the numbers in the solutions is: " << context.total << "\n";
			assert(context.total == 24702);
		}
		else
		{
			std::cout << "One or more threads did not complete successfully!\n";
			return 1;
		}
		
	#else
		
		ESudoku solver;
		int a;
		
		for(size_t i = 0; i < context.puzzles.size(); ++i)
		{
			if(!solver.load(context.puzzles.at(i)))
			{
				std::cout << "Failed to load puzzle!\n";
				return 1;
			}
			
			if(!solver.solve(true))
			{
				std::cout << "Failed to solve puzzle!\n";
				return 1;
			}
			
			puzzle = solver.getSolution();
			
			a = puzzle[0];
			a *= 10;
			a += puzzle[1];
			a *= 10;
			a += puzzle[2];
			
			context.total += a;
		}
		
		std::cout << "The sum of the numbers in the solution is: " << context.total << "\n";
		assert(context.total == 24702);
		
	#endif
	
	return 0;
}
