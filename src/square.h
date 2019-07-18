#pragma once

#include <SDL.h>
#include "enums.h"

class Square
{
public:
	Square(int cx, int cy, BlockColors color):
			center_x(cx),
      center_y(cy),
      color(color){};

	~Square(void);

public:
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

