#include "TetrisGame.h"

TetrisGame::TetrisGame(sf::RenderWindow* pWindow, sf::Sprite* pBlockSprite, Point gameboardOffset, Point nextShapeOffset)
{
	assert(pWindow != nullptr);
	assert(pBlockSprite != nullptr);

	this->pWindow = pWindow;
	this->pBlockSprite = pBlockSprite;
	this->gameboardOffset = gameboardOffset;
	this->nextShapeOffset = nextShapeOffset;

	reset();

	// setup our font for drawing the score
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf"))
	{
		assert(false && "Missing font: RedOctober.ttf");
	};
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(435, 325);


	//GridTetromino gt = GridTetromino();
	//gt.setShape(Tetromino::getRandomShape());
	
	//currentShape = gt;
	//currentShape.setGridLoc(board.getSpawnLoc());

}

TetrisGame::~TetrisGame()
{
	pBlockSprite = nullptr;
	pWindow = nullptr;
}

void TetrisGame::draw()
{
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	drawGameboard();
	pWindow->draw(scoreText);

}

void TetrisGame::onKeyPressed(sf::Event event)
{
	std::cout << "KEY INPUT " << std::endl;
	switch (event.key.code) {
		case (sf::Keyboard::Space):
			drop(currentShape);
			lock(currentShape);
			shapePlacedSinceLastGameLoop = true;
			break;
		case (sf::Keyboard::Left):
			attemptMove(currentShape, -1, 0);		
			break;
		case (sf::Keyboard::Right):
			attemptMove(currentShape, 1, 0);
			break;
		case (sf::Keyboard::Down):
			if (!attemptMove(currentShape, 0, 1)) {
				lock(currentShape);
				shapePlacedSinceLastGameLoop = true;
			}
			break;
		case (sf::Keyboard::Up):
			attemptRotate(currentShape);
			break;
	}
	std::vector<Point> m = currentShape.getBlockLocsMappedToGrid();
	std::string s;
	for (int i = 0; i < m.size(); i++) {
		s += m.at(i).toString();
	}
	//std::cout << "currentShape.gridLoc = " << currentShape.getGridLoc().toString() << std::endl;
	//std::cout << "mapped locs = " << s;
	//std::cout << "KEY INPUT - END" << std::endl;
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop)
{
	secondsSinceLastTick += secondsSinceLastLoop;
	if (secondsSinceLastTick > secsPerTick) { 
		tick(); 
		secondsSinceLastTick -= secsPerTick; 
	}

	if (shapePlacedSinceLastGameLoop) {
		if (spawnNextShape()) {
			pickNextShape();
			score += board.removeCompletedRows();
			updateScoreDisplay();
			determineSecsPerTick();
		}
		else {
			reset();
		}
	}
	shapePlacedSinceLastGameLoop = false;
}

void TetrisGame::tick()
{
	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
		shapePlacedSinceLastGameLoop = true;
	}
}

void TetrisGame::reset()
{
	score = 0;
	determineSecsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();
}

void TetrisGame::pickNextShape()
{
	nextShape.setShape(Tetromino::getRandomShape());
}

bool TetrisGame::spawnNextShape()
{
	currentShape = nextShape;
	currentShape.setGridLoc(board.getSpawnLoc());
	return(isPositionLegal(currentShape));
}

bool TetrisGame::attemptRotate(GridTetromino& shape)
{
	GridTetromino temp = GridTetromino(shape); //copy
	temp.rotateCW();
	if (!isPositionLegal(temp)) return false;
	shape.rotateCW();
	return true;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y)
{

	GridTetromino temp = GridTetromino(shape); //copy
	temp.move(x, y);
	if (!isPositionLegal(temp)) return false;
	shape.move(x, y);
	return true;
}

void TetrisGame::drop(GridTetromino& shape)
{
	while (attemptMove(shape, 0, 1)) {}
}

void TetrisGame::lock(const GridTetromino& shape)
{
	std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
	for (int i = 0; i < mappedLocs.size(); i++) {
		board.setContent(mappedLocs.at(i), shape.getColor());
	}
}

void TetrisGame::drawBlock(int x, int y, TetColor color, Point origin)
{

	pBlockSprite->setTextureRect(sf::IntRect(static_cast<int>(color)*BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
	pBlockSprite->setPosition(origin.getX() + (BLOCK_WIDTH*x), origin.getY() + (BLOCK_HEIGHT*y));
	pWindow->draw(*pBlockSprite);
}

void TetrisGame::drawGameboard()
{
	for (int x = 0; x < board.MAX_X; x++) {
		for (int y = 0; y < board.MAX_Y; y++) {
			if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK) drawBlock(x, y, 
				static_cast<TetColor>(board.getContent(x, y)), gameboardOffset);
		}
	}

	

}

//CHANGED PARAMETER "GridTetromino tetromino" to "GridTetromino& tetromino"
void TetrisGame::drawTetromino(GridTetromino& tetromino, Point origin)
{
	std::vector<Point> map = tetromino.getBlockLocsMappedToGrid();

	for (int i = 0; i < map.size(); i++) {
		drawBlock(map.at(i).getX(), map.at(i).getY(),
			tetromino.getColor(), origin);
	}
}

void TetrisGame::updateScoreDisplay()
{
	std::string scoreDisplay = "Score: " + std::to_string(score);
	scoreText.setString(scoreDisplay);
	std::cout << scoreDisplay << std::endl;
}

bool TetrisGame::isPositionLegal(const GridTetromino& shape)
{
	return (isShapeWithinBorders(shape) && !doesShapeIntersectLockedBlocks(shape));
}


bool TetrisGame::isShapeWithinBorders(const GridTetromino& shape)
{

	std::vector<Point> mappedBlocLocs = shape.getBlockLocsMappedToGrid();

	for (int i = 0; i < mappedBlocLocs.size(); i++) {
		Point p = mappedBlocLocs.at(i);
		if (p.getX() < 0 || 
			p.getX() >= board.MAX_X ||
			p.getY() >= board.MAX_Y
			 ) return false;
	}
	return true;
}

bool TetrisGame::doesShapeIntersectLockedBlocks(const GridTetromino& shape)
{
	return (!board.areLocsEmpty(shape.getBlockLocsMappedToGrid()));
}

void TetrisGame::determineSecsPerTick()
{
}
