#include "Point.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

// constructors
Point::Point() : x(0), y(0) {
}
Point::Point(int newX, int newY) : x(newX), y(newY) {
}

// getters & setters
int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}
void Point::setX(int x) {
	this->x = x;
}
void Point::setY(int y) {
	this->y = y;
}
void Point::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

// member functions
void Point::swapXY() { // swap x and y
	int t{ x };
	x = y;
	y = t;
}

void Point::multiplyX(int factor) { // multiply x by some factor
	x *= factor;
}
void Point::multiplyY(int factor) { // multiply y by some factor
	y *= factor;
}
// return a string in the form "[x,y]" to represent the state of 
// the Point instance (for debugging) Use stringstream:  							
// http://stev.org/post/cstringstreamexample for an example
std::string Point::toString() const {
	std::stringstream ss;
	ss << '[' << x << ',' << y << ']';
	return std::string{ ss.str() };
}