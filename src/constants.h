/*
define constants
*/

// Fow main window
#define WINDOW_CAPTION "Tetris" // window caption
#define WINDOW_WIDTH 892        // Window width
#define WINDOW_HEIGHT 714       // window height

// Game area
#define GAME_AREA_LEFT 0
#define GAME_AREA_RIGHT 612
#define GAME_AREA_BOTTOM WINDOW_HEIGHT
#define SQUARES_PER_ROW 18 // how many cells per row
#define SQUARES_PER_COL 21 // how many cells per col
#define SQUARES_SIZE 34    //
#define SQUARES_MEDIAN		17

// Game settings
#define GAME_LEVELS 5        // How many levels in the game
#define SCORE_PRE_LINE 125   //
#define SCORE_PRE_LEVEL 1300 //

#define BLOCK_DROP_SPEED 60
#define BLOCK_DROP_SPEED_UP 10 // Spead up when go to next level

#define SLIDE_TIME 15 // time can move the block after it touch bottom

// Block location
#define BLOCK_START_X 300
#define BLOCK_START_Y 72
#define NEXT_BLOCK_X (612 + 135)
#define NEXT_BLOCK_Y 140

// Location for drawing the game status
#define SCORE_AREA_LEFT GAME_AREA_RIGHT
#define SCORE_AREA_RIGHT WINDOW_WIDTH
#define SCORE_AREA_BOTTOM WINDOW_HEIGHT
#define SCORE_POSITION_X (612 + 60)
#define SCORE_POSITION_Y (65 + 180)
#define LEVEL_POSITION_X (612 + 60)
#define LEVEL_POSITION_Y 300
#define SCORE_PER_LEVEL_X (612 + 60)
#define SCORE_PER_LEVEL_Y 350
#define SPEED_X (612 + 60)
#define SPEED_Y 400

#define BLOCK_COLORS 5
#define BLOCK_TYPES 5