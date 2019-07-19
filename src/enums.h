#ifndef ENUMS_H
#define ENUMS_H

enum class GameStatus
{
	RUNNING,
	PAUSED,
	QUIT
};

// Block types
enum class BlockTypes
{
	SQUARE_BLOCK,		// 
  T_BLOCK,		// 
	L_BLOCK,		// 
	BACKWARDS_L_BLOCK,	// 
	STRAIGHT_BLOCK,		//
  S_BLOCK,		//
	BACKWARDS_S_BLOCK,	// 
};

//
enum class Directions
{
	LEFT,
	RIGHT,
	DOWN,
	NONE
};

enum BlockColors{
	Blue,
	Orange,
	Gray,
	Green,
	Red
};
#endif