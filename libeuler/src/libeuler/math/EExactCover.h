/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and
 *tools.
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

#ifndef INCLUDE_LIBEULER_MATH_EXACT_COVER_H
#define INCLUDE_LIBEULER_MATH_EXACT_COVER_H

#include <vector>
#include <utility>

/*!
 * \brief This class implements a structure to solve exact cover problems.
 *
 * We utilize Knuth's Algorithm DLX, described in his paper "P159 Dancing
 *links," which can be found
 * here: http://www-cs-faculty.stanford.edu/~uno/preprints.html
 *
 * More resources:
 *     http://en.wikipedia.org/wiki/Exact_cover
 *     http://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
 *     http://en.wikipedia.org/wiki/Dancing_Links
 */
class EExactCover
{
	// Forward declarations.
private:
	class EECNode;
	class EECHeader;
	class EECRoot;

public:
	EExactCover(int c = 0, int r = 0);
	virtual ~EExactCover();

	void clear();
	int getRows() const;
	int getColumns() const;
	void setSize(int c, int r);

	bool getAt(int c, int r) const;
	void setAt(int c, int r, bool v);
	int getColumnSize(int c) const;
	int getColumnName(int c) const;
	void setColumnName(int c, int n);

	void solve(bool s = false);
	std::vector<std::vector<std::pair<int, int>>> getSolutions() const;
	void clearSolutions();

private:
	bool single;
	std::vector<std::vector<EECNode *>> solutions;

	EECRoot *root;
	int rows, columns;

	EECHeader *columnByIndex(int c) const;
	EECNode *nodeByIndex(int c, int r) const;
	std::pair<int, int> indexFromNode(EECNode *n) const;

	void cover(EECHeader *c);
	void uncover(EECHeader *c);

	EECHeader *selectColumn();
	void search(int k, std::vector<EECNode *> &o);

private:
	/*!
	 * \brief This is an internal class that represents a generic node in
	 *our problem table.
	 *
	 * As per Knuth's description, we store either a "0" or a "1," and
	 *provide links to the nodes
	 * above, below, and to either side of this node, as well as to the
	 *header of the column we
	 * are a member of.
	 */
	class EECNode
	{
	public:
		EECNode *left;
		EECNode *right;
		EECNode *up;
		EECNode *down;
		EECHeader *column;
		bool data;

		EECNode(EECHeader *c);
		virtual ~EECNode();

		virtual void setData(bool d);
	};

	/*!
	 * \brief This is an internal class that represents a column header in
	 *our problem table.
	 *
	 * As per Knuth's description, this implements everything a node does
	 *EXCEPT data storage,
	 * and it also adds the name and size fields.
	 */
	class EECHeader : public EECNode
	{
	public:
		int name;
		int size;

		EECHeader(EECRoot *r);
		virtual ~EECHeader();

	private:
		virtual void setData(bool d);
	};

	/*!
	 * \brief This is an internal class that represents a root node in our
	 *problem table.
	 *
	 * As per Knuth's description, this implements everything a header does
	 *EXCEPT the up and
	 * down links, the column link, and the size and name fields.
	 */
	class EECRoot : public EECHeader
	{
	public:
		EECRoot();
		virtual ~EECRoot();
	};
};

#endif
