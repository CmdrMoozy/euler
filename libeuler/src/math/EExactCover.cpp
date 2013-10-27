#include "EExactCover.h"

#include "EDefines.h"

/***********************************
 ************* EECNode *************
 ***********************************/

/*!
 * This constructor creates a new, empty, unlinked node with the given column header as a parent.
 * Note that our L, R, U and D links are NULL initially, and our data is initially "0".
 *
 * \param c The header of the column this node is a member of.
 */
EExactCover::EECNode::EECNode(EExactCover::EECHeader *c)
	: left(NULL), right(NULL), up(NULL), down(NULL), column(c), data(false)
{
}

/*!
 * This is our default destructor, which cleans up and destroys our node.
 */
EExactCover::EECNode::~EECNode()
{
}

/*!
 * This accessor sets our node's data. Note that setting the data manually (e.g., by doing node->data = false)
 * can lead to unexpected behavior, because the node's column's size will not be updated accordingly. This can
 * lead to the dancing links algorithm never terminating, or at the very least getting the correct answer much
 * more slowly than it might have otherwise.
 *
 * \param d Our new data.
 */
void EExactCover::EECNode::setData(bool d)
{
	// Update our header's size, if appropriate.
	
	if(data ^ d)
	{
		if(d)
			++column->size;
		else
			--column->size;
	}
	
	// Set our new data.
	
	data = d;
}

/***********************************
 ************ EECHeader ************
 ***********************************/

/*!
 * This constructor creates a new column header, with the given root node. Note that, by default, our up and
 * down links point back to us (because we are a valid, empty column) and our left and right links are initialized
 * to NULL.
 *
 * \param r The root node this column is a member of.
 */
EExactCover::EECHeader::EECHeader(EExactCover::EECRoot *r)
	: EExactCover::EECNode(r), name(0), size(0)
{
	this->up = this;
	this->down = this;
	this->left = NULL;
	this->right = NULL;
}

/*!
 * This is our default destructor, which cleans up and destroys our column. Note that this destructor automatically
 * deletes any nodes that have been correctly linked to our column's list.
 */
EExactCover::EECHeader::~EECHeader()
{
	EExactCover::EECNode *c = this->down, *n;
	while( (c != NULL) && (c != this) )
	{
		n = c->down;
		delete c;
		c = n;
	}
}

/*!
 * We override our superclass's accessor, because headers do not store data.
 *
 * \param d Our new data - unused.
 */
void EExactCover::EECHeader::setData(bool EUNUSED(d))
{
}

/***********************************
 ************* EECRoot *************
 ***********************************/

/*!
 * This constructor creates a new root node. Note that our left and right links are initialized to point
 * back to us, as we represent an empty root list.
 */
EExactCover::EECRoot::EECRoot()
	: EExactCover::EECHeader(NULL)
{
	this->left = this;
	this->right = this;
}

/*!
 * This is our default constructor, which cleans up and destroys our root list. Note that this destructor auomatically
 * deletes any column headers that have been correctly linked to our root node.
 */
EExactCover::EECRoot::~EECRoot()
{
	EExactCover::EECNode *c = this->right, *n;
	while( (c != NULL) && (c != this) )
	{
		n = c->right;
		delete c;
		c = n;
	}
}

/***********************************
 *********** QExactCover ***********
 ***********************************/

/*!
 * This constructor initializes a new exact cover object of a given size (or empty). Note that if
 * the dimensions provided are invalid (i.e., are negative, or are zero), we initialize an empty
 * object which can be resized with setSize() later.
 *
 * \param c The number of columns this exact cover should contain.
 * \param r The number of rows this exact cover should contain.
 */
EExactCover::EExactCover(int c, int r)
	: single(false), root(NULL), rows(0), columns(0)
{
	setSize(c, r);
}

/*!
 * This is our default destructor, which cleans up and destroys our object.
 */
EExactCover::~EExactCover()
{
	clear();
}

/*!
 * This function clears our object of all data - it is equivalent to calling setSize(0, 0).
 */
void EExactCover::clear()
{
	if(root != NULL) delete root;
	root = NULL;
	columns = rows = 0;
}

/*!
 * This function returns the number of rows our object contains.
 *
 * \return Our row count.
 */
int EExactCover::getRows() const
{
	return rows;
}

/*!
 * This function returns the number of columns our object contains (ignoring covered columns).
 *
 * \return Our column count.
 */
int EExactCover::getColumns() const
{
	return columns;
}

/*!
 * This function resizes our object, making room for a new problem. Note that if either c or r are less than
 * or equal to zero, this does the same thing as calling clear().
 *
 * \param c The number of columns our object should contain.
 * \param r The number of rows our object should contain.
 */
void EExactCover::setSize(int c, int r)
{
	clear();
	if( (c <= 0) || (r <= 0) ) return;
	
	// Create our root node.
	
	root = new EExactCover::EECRoot();
	
	// Create our column headers.
	
	for(int i = 0; i < c; ++i)
	{
		EExactCover::EECHeader *h = new EExactCover::EECHeader(root);
		
		h->right = root;
		h->left = root->left;

		h->left->right = h;
		h->right->left = h;
		
		h->name = i;
	}
	
	EExactCover::EECHeader *lastCol = dynamic_cast<EExactCover::EECHeader *>(root->left),
		*firstCol = dynamic_cast<EExactCover::EECHeader *>(root->right);
	
	// Create our nodes.
	
	EExactCover::EECHeader *header = root;
	for(int i = 0; i < c; ++i)
	{
		header = dynamic_cast<EExactCover::EECHeader *>(header->right);
		
		for(int j = 0; j < r; ++j)
		{
			EExactCover::EECNode *n = new EExactCover::EECNode(header);
			
			n->up = header->up;
			n->down = header;
			
			n->up->down = n;
			n->down->up = n;
			
			if(header != firstCol)
			{
				n->left = n->up->left->down;
				n->left->right = n;
			}
		}
	}
	
	// Link toroidally horizontally.
	
	EExactCover::EECNode *ln = lastCol->down, *fn = firstCol->down;
	for(int i = 0; i < r; ++i)
	{
		ln->right = fn;
		fn->left = ln;
		
		ln = ln->down;
		fn = fn->down;
	}
	
	rows = r;
	columns = c;
}

/*!
 * This function returns the data stored by the node at the given index in our object. Note that if
 * c or r are out-of-bounds, we simply return false.
 *
 * \param c The column of the desired data.
 * \param r The row of the desired data.
 * \return The data stored at the given index, or false on error.
 */
bool EExactCover::getAt(int c, int r) const
{
	EExactCover::EECNode *node = nodeByIndex(c, r);
	if(node == NULL) return false;
	
	return node->data;
}

/*!
 * This function sets the data stored by the node at the given index in our object. Note that if
 * c or r are out-of-bounds, we simply return without setting anything.
 *
 * \param c The column of the destination node.
 * \param r The row of the destination node.
 * \param v The new data this node should store.
 */
void EExactCover::setAt(int c, int r, bool v)
{
	EExactCover::EECNode *node = nodeByIndex(c, r);
	if(node == NULL)
		return;
	
	node->setData(v);
}

/*!
 * This function returns the size of the column at the given index (that is, the number of "1" nodes
 * it contains). Note that the size is re-calculated each time, so this function is (relatively speaking)
 * slow when called repeatedly. Note that if the given index is out-of-bounds, we return -1.
 *
 * \param c The index of the desired column.
 * \return The column's size, or -1 on error.
 */
int EExactCover::getColumnSize(int c) const
{
	EExactCover::EECHeader *column = columnByIndex(c);
	if(column == NULL) return -1;
	
	return column->size;
}

/*!
 * This function returns the name of the column at the given index. Note that if the given index is out-of-bounds,
 * we simply return a default name of 0.
 *
 * \param c The index of the desired column.
 * \return The column's name, or 0 on error.
 */
int EExactCover::getColumnName(int c) const
{
	EExactCover::EECHeader *column = columnByIndex(c);
	if(column == NULL) return 0;
	
	return column->name;
}

/*!
 * This function sets the name of the column at the given index. Note that if the given index is out-of-bounds, 
 * we simply return without setting anything.
 *
 * \param c The index of the desired column.
 * \param n The column's new name.
 */
void EExactCover::setColumnName(int c, int n)
{
	EExactCover::EECHeader *column = columnByIndex(c);
	if(column == NULL) return;
	
	column->name = n;
}

/*!
 * This function attempts to solve the exact cover problem we are currently storing. Note that the exact cover problem is
 * NP-complete, so this can take a long problem depending on problem complexity.
 *
 * \param s True means we terminate after finding a single solution.
 */
void EExactCover::solve(bool s)
{
	single = s;
	clearSolutions();
	
	// If our object is empty, just return.
	if( (getColumns() <= 0) || (getRows() <= 0) ) return;
	
	std::vector<EExactCover::EECNode *> o;
	search(0, o);
}

/*!
 * This function returns the list of solutions in a usable format - returned is a list of solutions, where each solution
 * is a list of (column,row) indices that make up the solution. Note that if you haven't already called solve(), this will
 * just return an empty list.
 *
 * \return A list of the solutions.
 */
std::vector< std::vector< std::pair<int, int> > > EExactCover::getSolutions() const
{
	std::vector< std::vector< std::pair<int, int> > > ret;
	
	for(unsigned int i = 0; i < solutions.size(); ++i)
	{ // For each solution...
		std::vector< std::pair<int, int> > s;
		
		for(unsigned int j = 0; j < solutions[i].size(); ++j)
		{ // For each node involved in the solution...
			EExactCover::EECNode *n = solutions[i][j];
			do
			{
				
				if(n->data)
					s.push_back(indexFromNode(n));
				
				n = n->right;
				
			} while(n != solutions[i][j]);
		}
		
		ret.push_back(s);
	}
	
	// Return a list of solutions, where each solution is a list of col,row indices.
	
	return ret;
}

/*!
 * This function simply clears the current list of solutions.
 */
void EExactCover::clearSolutions()
{
	solutions.clear();
}

/*!
 * This function returns a pointer to the column specified by index. We retrieve the pointer by iterating through our
 * root node's column list, so this function's behavior is undefined if any columns have been covered. If the given index
 * is out-of-bounds, or some other error (probably involving covering) occurs, NULL is returned instead.
 *
 * \param c The index of the column desired.
 * \return A pointer to the desired column, or NULL on error.
 */
EExactCover::EECHeader *EExactCover::columnByIndex(int c) const
{
	if( (c < 0) || (c >= getColumns()) )
		return NULL;
	
	EExactCover::EECNode *col = root->right;
	for(int i = 0; i < c; ++i)
	{
		if(col == root) return NULL;
		col = col->right;
	}
	
	return dynamic_cast<EExactCover::EECHeader *>(col);
}

/*!
 * This function returns a pointer to the node specified by index. We retrieve the pointer by iterating thorugh our list,
 * so this function's behavior is undefined if any columns have been covered. Because covering a column also removes vertical
 * links on nodes in other columns, there is no way for this function to accurately tell what row it is on. If the given
 * index is out-of-bounds, or some other error (probably involving covering) occurs, NULL is returned instead.
 *
 * \param c The column of the node desired.
 * \param r The row of the node desired.
 * \return A pointer to the node desired, or NULL on error.
 */
EExactCover::EECNode *EExactCover::nodeByIndex(int c, int r) const
{
	if( (c < 0) || (c >= getColumns()) || (r < 0) || (r >= getRows()) )
		return NULL;
	
	EExactCover::EECHeader *col = columnByIndex(c);
	if(col == NULL) return NULL;
	
	EExactCover::EECNode *node = col->down;
	for(int i = 0; i < r; ++i)
	{
		if(node == col) return NULL;
		node = node->down;
	}
	
	return node;
}

/*!
 * This is a convenience function that determines the index of the given node in our table. Note that, if the node given is
 * in reality a column header or the root node, or is NULL, then an index of -1,-1 is returned instead. Also note that if
 * any columns are cover()'ed when this function is called, the results are undefined.
 *
 * \param n The node whose index is to be determined.
 * \return A (column,row) index of the given node.
 */
std::pair<int, int> EExactCover::indexFromNode(EExactCover::EECNode *n) const
{
	int col = -1, row = -1;
	
	if( (n != NULL) && (dynamic_cast<EExactCover::EECRoot *>(n) == NULL) &&
		(dynamic_cast<EExactCover::EECHeader *>(n) == NULL) )
	{ // If this is a NODE, and not a header or root, and it isn't itself NULL...
		
		// Determine the column.
		EExactCover::EECNode *c = root->right;
		col = 0;
		while(c != n->column)
		{
			++col;
			c = c->right;
		}
		
		// Determine the row.
		EExactCover::EECNode *r = n->column->down;
		row = 0;
		while(r != n)
		{
			++row;
			r = r->down;
		}
		
	}
	
	return std::pair<int, int>(col, row);
}

/*!
 * This function performs a "cover" operation on the given column. This means, we "temporarily" remove the column from
 * the root node's list, and we also vertically cover any "1" nodes on the same row as "1" nodes in this column. If the
 * column is already covered, then no action is taken - as such, recursive calls to this function will not break anything
 * (although you really shouldn't be doing that anyway , in all likelihood).
 *
 * Note that the order you cover/uncover things in is important, and things will break if you don't do it correctly. See
 * Knuth's "Dancing Links," pp. 7 for more information. Because cover affects nodes in other columns, if you don't uncover
 * correctly, you can cause us to leak memory!
 *
 * \param c The column to cover.
 */
void EExactCover::cover(EExactCover::EECHeader *c)
{
	// If we're given an invalid column, do nothing.
	if(c == NULL) return;
	
	// If the column is already covered, do nothing.
	if( (c->right->left == c->left) &&
		(c->left->right == c->right) )
	{
		return;
	}
	
	// Cover this column.
	c->right->left = c->left;
	c->left->right = c->right;
	
	EExactCover::EECNode *i = c->down;
	while(i != c)
	{ // For each node in this column...
		
		// If this node is a "1" node...
		if(i->data)
		{
			EExactCover::EECNode *j = i->right;
			while(j != i)
			{ // For each node on this node's row, in OTHER columns...
				
				// If this node is a "1" node...
				if(j->data)
				{
					// Cover this node.
					
					j->down->up = j->up;
					j->up->down = j->down;
					
					// Update the node's column's size, if appropriate.
					
					if(j->data)
						--j->column->size;
					
				}
				
				// Increment our node.
				j = j->right;
				
			}
		}
		
		// Increment our row.
		i = i->down;
		
	}
}

/*!
 * This function performs an "uncover" operation on the given column. This means, we add the column back to the root
 * node's list, and we also vertically uncover any "1" nodes on the same row as "1" nodes in this column. If the
 * column is already uncovered, then no action is taken - as such, recursive calls to this function will not break anything 
 * (although you really shouldn't be doing that anyway, in all likelihood).
 *
 * Note that the order you cover/uncover things in is important, and things will break if you don't do it correctly. See
 * Knuth's "Dancing Links," pp. 7 for more information. Because cover affects nodes in other columns, if you don't uncover
 * correctly, you can cause us to leak memory!
 *
 * \param c The column to uncover.
 */
void EExactCover::uncover(EExactCover::EECHeader *c)
{
	// If we're given an invalid column, do nothing.
	if(c == NULL) return;
	
	// If the column is already uncovered, do nothing.
	if( (c->right->left == c) && (c->left->right == c) )
		return;
	
	EExactCover::EECNode *i = c->up;
	while(i != c)
	{ // For each node in this column...
		
		// If this is a "1" node...
		if(i->data)
		{
			EExactCover::EECNode *j = i->left;
			while(j != i)
			{
				// If this is a "1" node...
				if(j->data)
				{
					// Uncover this node.
					
					j->down->up = j;
					j->up->down = j;
					
					// Update the node's column's size, if appropriate.
					
					if(j->data)
						++j->column->size;
				}
				
				// Increment our node.
				j = j->left;
			}
		}
		
		// Increment our row.
		i = i->up;
		
	}
	
	// Uncover this column.
	c->right->left = c;
	c->left->right = c;
}

/*!
 * This is a helper function that selects the next column we should cover in search(). We try to pick the lowest-sized
 * column closest to the root node in the list, as per Knuth's "Dancing Links," pp. 6. This slightly complicated selection
 * is done to reduce branching in search().
 *
 * \return A pointer to the next column.
 */
EExactCover::EECHeader *EExactCover::selectColumn()
{	
	EExactCover::EECHeader *c = NULL;
	int s = getRows() + 1;
	
	EExactCover::EECHeader *j = dynamic_cast<EExactCover::EECHeader *>(root->right);
	while(j != root)
	{
		if(j->size < s)
		{
			c = j;
			s = j->size;
		}
		
		j = dynamic_cast<EExactCover::EECHeader *>(j->right);
	}
	
	return c;
}

/*!
 * This is the function that implement's Knuth's Algorithm DLX, which finds solutions to exact cover problems. See Knuth's
 * "Dancing Links," pp. 5-8. Note that we add solutions we find directly to "solutions," so our caller should probably
 * clear that list before calling search(). Also note that the initial call to this function should be search(0, o).
 *
 * \param k The current search level.
 * \param o A buffer for the current solution.
 */
void EExactCover::search(int k, std::vector<EExactCover::EECNode *> &o)
{
	// If we are in single mode and a solution has already been found, stop recursing.
	
	if(single && (solutions.size() > 0)) return;
	
	// If all columns are covered, we have found a solution, so return.
	if(root->right == root)
	{
		// Grab nodes O[0] ... O[k-1] as the current solution.
		std::vector<EExactCover::EECNode *> solution;
		solution.resize(k, NULL);
		for(int i = 0; i < k; ++i)
			solution[i] = o[i];
		
		// Add this to our solutions list, and terminate.
		solutions.push_back(solution);
		return;
	}
	
	// Select a column, c.
	EExactCover::EECHeader *c = selectColumn();
	
	// Cover c.
	cover(c);
	
	EExactCover::EECNode *r = c->down;
	while(r != c)
	{ // For each node in this column...
		
		// If this node is a "1" node...
		if(r->data)
		{
			// Set O[k] = r.
			if( o.size() <= static_cast<unsigned int>(EABS(k)) ) o.resize(k+1, NULL);
			o[k] = r;
			
			EExactCover::EECNode *j = r->right;
			while(j != r)
			{ // For each other node on this row...
				
				// If this node is a "1" node...
				if(j->data)
				{
					// Cover the column this node belongs to.
					cover(j->column);
				}
				
				// Increment our node.
				j = j->right;
				
			}
			
			// Search recursively.
			search(k+1, o);
			
			// Set r = o[k] and c to the column containing r.
			r = o[k];
			c = r->column;
			
			j = r->left;
			while(j != r)
			{ // For each other node on this row...
				
				// If this node is a "1" node...
				if(j->data)
				{
					// Uncover the column this node belongs to.
					uncover(j->column);
				}
				
				// Increment our node.
				j = j->left;
				
			}
		}
		
		// Increment our node.
		r = r->down;
	}
	
	// Uncover our original column.
	uncover(c);
}
