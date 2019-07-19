
#pragma once
#include <vector>
#include "SDL.h"

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
	Square **GetSquares();

private:
	int center_x;
	int center_y;
	BlockTypes type;
	BlockColors color;
	Square *squares[4];
};
