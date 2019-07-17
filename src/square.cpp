#include "constants.h"
#include "square.h"


void Square::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = {
		this->center_x - SQUARES_MEDIAN, this->center_y - SQUARES_MEDIAN,
		SQUARES_MEDIAN * 2, SQUARES_MEDIAN * 2
	};
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
}

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
