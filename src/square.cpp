#include "constants.h"
#include "square.h"

void Square::Move(Directions dir)
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
}

Square::~Square(void)
{

}
