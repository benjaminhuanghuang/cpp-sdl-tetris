
#pragma once
#include <vector>
#include <array>
#include "SDL.h"
#include "enums.h"
#include "square.h"

class Block
{
public:
	Block(int cx, int cy, BlockTypes type, BlockColors color);
	Block(BlockTypes type, BlockColors color);

	~Block(void);

public:
	void SetupBlock(int x, int y, BlockColors color);
	void Move(Directions dir);
	void Rotate();
	std::vector<SDL_Point> GetRotatedPositions();
	std::vector<SDL_Point> GetMoveLeftPositions();
	std::vector<SDL_Point> GetMoveRightPositions();
	std::vector<SDL_Point> GetMoveDownPositions();
	BlockTypes getBlockType() const;
	BlockColors getBlockColor() const;
	std::array<std::shared_ptr<Square>, 4> GetSquares();

	int getCenterX() {return center_x;};
	int getCenterY() {return center_y;};
private:
	int center_x;
	int center_y;
	BlockTypes type;
	BlockColors color;
	std::array<std::shared_ptr<Square>, 4> squares;
};
