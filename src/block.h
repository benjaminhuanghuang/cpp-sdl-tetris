
#include "square.h"
#include "enums.h"

class Block
{
public:
	Block(int center_x, int center_y, BlockTypes type, BlockColors color) : center_x(center_x),
																																					center_y(center_y),
																																					type(type),
																																					color(color){};
	Block(BlockTypes type, BlockColors color) : center_x(center_x),
																							center_y(center_y),
																							type(type),
																							color(color){};
	~Block(void);

public:
	void SetupBlock(int x, int y, BlockColors color);
	void DrawSquares(SDL_Renderer *renderer);
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
