// The Gameboard class encapsulates the functionality of the Tetris game board.
// It is essentially a grid of blocks, and we will implement it with a 2D array.



#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"
#include <iostream>
#include <iomanip>
#include <assert.h>

class Gameboard
{
public:
	// CONSTANTS
	static const int MAX_X = 10;		// gameboard x dimension
	static const int MAX_Y = 19;		// gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// contents of an empty block

	// MEMBER FUNCTIONS


	// constructor - empty() the grid
	Gameboard();

	// return the content at a given point
	int getContent(Point pt) const;
	// return the content at an x,y grid loc
	int getContent(int x, int y) const;

	// set the content at a given point
	void setContent(Point pt, int content);
	// set the content at an x,y grid loc
	void setContent(int x, int y, int content);

	// set the content for an array of grid locs
	void setContent(std::vector<Point> locs, int content);


	// return true if the content at ALL (valid) points is empty
	//   *** IMPORTANT NOTE: invalid x,y values can be passed to this method.
	//   Invalid meaning: outside the bounds of the grid.
	//   * ONLY TEST VALID POINTS (disregard the others - and ensure you
	//   don't use them to index into the grid).  Testing invalid points
	//   would likely result in an out of bounds error or segmentation fault!
	//   If no points are valid, return true
	bool areLocsEmpty(std::vector<Point> locs) const;

	// removes all completed rows from the board
	//   use getCompletedRowIndices() and removeRows() 
	//   return the # of completed rows removed
	int removeCompletedRows();

	// fill the board with EMPTY_BLOCK 
	//   (iterate through each rowIndex and fillRow() with EMPTY_BLOCK))
	void empty();

	// getter for the spawnLoc for new blocks
	Point getSpawnLoc() const;

	// print the grid contents to the console (for debugging purposes)
	//   use std::setw(2) to space the contents out (#include <iomanip>).
	void printToConsole() const;


private:
	// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
	bool isRowCompleted(int rowIndex) const;

	// scan the board for completed rows.
	//   Iterate through grid rows and use isRowCompleted(rowIndex)
	//   return a vector of completed row indices.
	std::vector<int> getCompletedRowIndices() const;

	// In gameplay, when a full row is completed (filled with content)
	// it gets "removed".  To be exact, the row itself is not removed
	// but the content from the row above it is copied into it.
	// This continues all the way up the grid until the first row
	// is copied into the second row.  Finally, the first row is 
	// filled with EMPTY_BLOCK
	// given a row index:
	//   1) Starting at rowIndex, copy each row above the removed
	//     row "one-row-downwards" in the grid.
	//     (loop from y=rowIndex down to 0, and copyRowIntoRow(y-1, y)).
	//   2) call fillRow() on the first row (and place EMPTY_BLOCKs in it).
	void removeRow(int rowIndex);

	// given a vector of row indices, remove them 
	//   (iterate through the vector and and call removeRow()
	//   on each row index). 
	void removeRows(std::vector<int> rowIndices);

	// fill a given grid row with specified content
	void fillRow(int rowIndex, int content);

	// copy a source row's contents into a target row.
	void copyRowIntoRow(int sourceRowIndex, int targetRowIndex);


	// MEMBER VARIABLES -------------------------------------------------

	// the gameboard - a grid of X and Y offsets.  
	//  ([0][0] is top left, [MAX_X][MAX_Y] is bottom right) 
	int grid[MAX_X][MAX_Y];
	// the gameboard offset to spawn a new tetromino at.
	const Point spawnLoc{ MAX_X / 2, 0 };

	// FRIENDS
// for testing purposes (allows TestSuite to access private members of this class)
	friend class TestSuite;
};

#endif /* GAMEBOARD_H */

