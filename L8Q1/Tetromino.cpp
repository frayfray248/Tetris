#include "Tetromino.h"
#include <iostream>

// constructors
Tetromino::Tetromino() {
	setShape(TetShape::SHAPE_I);
};

// getters & setters
TetColor Tetromino::getColor() const {
	return this->color;
}
TetShape Tetromino::getShape() const {
	return this->shape;
}

// member functions
void Tetromino::setShape(TetShape shape) {// set the shape
	blockLocs.clear();
	this->shape = shape;
	switch (shape) {
	case SHAPE_O:
		blockLocs = { Point(0, 0), Point(1,0), Point(0,1), Point(1,1) };
		color = TetColor::YELLOW;
		break;
	case SHAPE_I:
		blockLocs = { Point(0, 0), Point(0,-1), Point(0,1), Point(0,2) };
		color = TetColor::BLUE_LIGHT;
		break;
	case SHAPE_S:
		blockLocs = { Point(0, 0), Point(-1,0), Point(0,1), Point(1,1) };
		color = TetColor::RED;
		break;
	case SHAPE_Z:
		blockLocs = { Point(0, 0), Point(0,1), Point(-1,1), Point(1,0) };
		color = TetColor::GREEN;
		break;
	case SHAPE_L:
		blockLocs = { Point(0, 0), Point(0,1), Point(0,-1), Point(1,-1) };
		color = TetColor::ORANGE;
		break;
	case SHAPE_J:
		blockLocs = { Point(0, 0), Point(0,1), Point(0,-1), Point(-1,-1) };
		color = TetColor::BLUE_DARK;
		break;
	case SHAPE_T:
		blockLocs = { Point(0, 0), Point(-1,0), Point(1,0), Point(0,-1) };
		color = TetColor::PURPLE;
		break;
	default:
		blockLocs = { Point(0, 0), Point(1,0), Point(0,1), Point(1,1) };
		color = TetColor::YELLOW;
		break;
	}
}

TetShape Tetromino::getRandomShape() {
	int num = rand() % 7 + 1;
	return static_cast<TetShape>(num);

}

void Tetromino::rotateCW() {		// rotate the shape 90 degrees around [0,0] (clockwise)
				// to do this:
				//  - iterate through blockLocs
				//  - rotate each Point 90 degrees around [0,0]
				// hint: rotate the point [1,2] clockwise around [0,0] and note
				// how the x,y values change. There are 2 functions in the Point
				// class that can be used to accomplish a rotation.	 
	for (int i = 0; i < blockLocs.size(); i++) {
		blockLocs.at(i).swapXY();
		blockLocs.at(i).multiplyY(-1);
	}
}


void Tetromino::printToConsole() const {	// print a grid to display the current shape
				// to do this:
				// print out a “grid” of text to represent a co-ordinate
				// system.  Start at top left [-3,3] go to bottom right [3,-3]
				// (use nested for loops)
				//  for each [x,y] point, loop through the blockLocs and if
				//  the point exists in the list, print an 'x' instead of a '.'
				// You should end up with something like this:
				// (results will vary depending on shape and rotation, eg: this
				//  one shows a T shape rotated clockwise once)
				//  .......
				//  .......
				//  ...x...
				//  ..xx...
				//  ...x...
				//  .......
	for (int y = 3; y > -3; y--) {
		for (int x = -3; x < 3; x++) {
			if (pointExists(x, y)) std::cout << 'x';
			else std::cout << '.';
		}
		std::cout << std::endl;
	}
}

bool Tetromino::pointExists(int x, int y) const {
	for (int p = 0; p < blockLocs.size(); p++)
		if (blockLocs.at(p).getX() == x && blockLocs.at(p).getY() == y) {
			return true;
		}
	return false;
}