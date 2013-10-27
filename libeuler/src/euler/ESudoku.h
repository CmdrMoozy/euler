#ifndef INCLUDE_LIBEULER_EULER_SUDOKU_H
#define INCLUDE_LIBEULER_EULER_SUDOKU_H

#include <vector>
#include <cstdint>

// Forward declarations.
class EExactCover;

/*!
 * \brief This class implements a simple Sudoku solver.
 *
 * We utilize the dancing links algorithm, implemented by EExactCover, to solve these problems.
 * More information about this technique can be found in the following article:
 *     http://www.ams.org/samplings/feature-column/fcarc-kanoodle
 */
class ESudoku
{
	public:
		ESudoku();
		virtual ~ESudoku();
		
		void clear();
		bool load(const std::vector<int> &p);
		bool solve(bool s = false);
		std::vector<int> getSolution() const;
		
	private:
		std::vector<int> puzzle;
		std::vector<int> solution;
		EExactCover *solver;
		
		void updateMasks(std::vector<uint16_t> &m, int i, int v);
		void reduce(std::vector<uint16_t> &m, int i);
		bool optimizePairs(std::vector<uint16_t> &m);
		void preprocess();
		
		int rowOf(int i) const;
		int colOf(int i) const;
		int boxOf(int i) const;
	
		int rowIndex(int r, int i) const;
		int colIndex(int c, int i) const;
		int boxIndex(int b, int i) const;
};

#endif
