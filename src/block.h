
#pragma once

#include "square.h"
#include "enums.h"

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
	int *GetRotatedPositions();
	BlockTypes getBlockType() const;

	Square **GetSquares();

private:
	int center_x;
	int center_y;
	BlockTypes type;
	BlockColors color;
	Square *squares[4];
};
