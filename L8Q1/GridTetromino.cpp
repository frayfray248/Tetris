#include "GridTetromino.h"

GridTetromino::GridTetromino()
{
	gridLoc = Point(0, 0);
}

GridTetromino::GridTetromino(const GridTetromino &copy) {
	this->gridLoc = copy.gridLoc;
	setShape(copy.getShape());
	this->blockLocs = copy.blockLocs;
}

Point GridTetromino::getGridLoc() const
{
	return gridLoc;
}

void GridTetromino::setGridLoc(int x, int y)
{
	gridLoc.setXY(x, y);
}

void GridTetromino::setGridLoc(const Point& pt)
{
	gridLoc = pt;
}

void GridTetromino::move(int xOffset, int yOffset)
{
	gridLoc.setXY(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const
{
	std::vector<Point> mappedBlockLocs;

	for (int i = 0; i < blockLocs.size(); i++) {
		mappedBlockLocs.push_back(
			Point(gridLoc.getX() + blockLocs.at(i).getX(),
				gridLoc.getY() + blockLocs.at(i).getY()));
	}

	return mappedBlockLocs;
}
