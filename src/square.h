#include <SDL.h>
#include "enums.h"

class Square
{
public:
	Square(int center_x, int center_y, BlockColors color):
			center_x(center_x),
      center_y(center_y),
      color(color){};

	~Square(void);

public:
	void Draw(SDL_Renderer* renderer);
	void Move(Directions dir);

public:
	int getCenter_x() const { return center_x; }
	int getCenter_y() const { return center_y; }

	void setCenter_x(int x) { center_x = x; }
	void setCenter_y(int y) { center_y = y; }
	void setColor(BlockColors c) { color = c; }

private:
	int center_x;				
	int center_y;				
	BlockColors color;
};

