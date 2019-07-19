#include "block.h"
#include "constants.h"



Block::Block(int center_x, int center_y, BlockTypes type, BlockColors color):
	type(type), color(color)
{
	this->center_x = center_x;
	this->center_y = center_y;
	
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}

	SetupBlock(center_x, center_y, color);
}

Block::Block(BlockTypes type, BlockColors color):
	type(type), color(color)
{
	center_x = 0;
	center_y = 0;
	
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}
}

void Block::SetupBlock(int x, int y, BlockColors color)
{
	center_x = x;
	center_y = y;
	
	for (int i=0; i<4; ++i)
	{
		if (squares[i] != nullptr)
		{
			delete squares[i];
			squares[i] = nullptr;
		}
	}

	switch (type)
	{
	case BlockTypes::SQUARE_BLOCK:			
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[2] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
		}
		break;
	case BlockTypes::T_BLOCK:				
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[1] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[3] = new Square(x - SQUARES_MEDIAN * 3, y + SQUARES_MEDIAN, color);
		}
		break;
	case BlockTypes::L_BLOCK:				
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, color);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, color);
		}
		break;
	case BlockTypes::BACKWARDS_L_BLOCK:		
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[1] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[3] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, color);
		}
		break;
	case BlockTypes::STRAIGHT_BLOCK:		
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN * 3, color);
			squares[1] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[2] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, color);
		}
		break;
	case BlockTypes::S_BLOCK:			
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[2] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, color);
		}
		break;
	case BlockTypes::BACKWARDS_S_BLOCK:		
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, color);
			squares[1] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, color);
			squares[3] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, color);
		}
		break;
	default:
		break;
	}
}

void Block::Move(Directions dir)
{
	switch (dir)
	{
	case Directions::LEFT:
		center_x -= SQUARES_SIZE;
		break;
	case Directions::RIGHT:
		center_x += SQUARES_SIZE;
		break;
	case Directions::DOWN:
		center_y += SQUARES_SIZE;
		break;
	default:
		break;
	}

	for (int i=0; i<4; ++i)
	{
		squares[i]->Move(dir);
	}
}

void Block::Rotate()
{
	for (int i=0; i<4; ++i)
	{
		int x = squares[i]->getCenter_x();
		int y = squares[i]->getCenter_y();
		
		x -= center_x;
		y -= center_y;

		int x2 = -y;
		int y2 = x;

		x2 += center_x;
		y2 += center_y;

		squares[i]->setCenter_x(x2);
		squares[i]->setCenter_y(y2);
	}
}

int* Block::GetRotatedPositions()
{
	int* SquaresPositions = new int[8];

	for (int i=0; i<4; ++i)
	{
		int x = squares[i]->getCenter_x();
		int y = squares[i]->getCenter_y();
		
		x -= center_x;
		y -= center_y;

		int x2 = -y;
		int y2 = x;

		x2 += center_x;
		y2 += center_y;

		SquaresPositions[i*2] = x2;
		SquaresPositions[i*2+1] = y2;
	}
	return SquaresPositions;
}

Square** Block::GetSquares()
{
	return squares;
}

BlockTypes Block::getBlockType() const
{
	return type;
}

BlockColors Block::getBlockColor() const
{
	return color;
}

Block::~Block(void)
{
	for (int i=0; i<4; ++i)
	{
		if (squares[i])
			delete squares[i];
	}
}
