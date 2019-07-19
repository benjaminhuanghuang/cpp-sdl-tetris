#include <iostream>
#include <memory>
#include "SDL.h"
#include "game.h"
#include "constants.h"
#include "enums.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_color(0, static_cast<int>(BLOCK_COLORS)),
      random_type(0, static_cast<int>(BLOCK_TYPES))
{
}

void Game::Init()
{
  BlockColors color = (BlockColors)(random_color(engine));
  BlockTypes type = (BlockTypes)(random_type(engine));
  CurrentBlock = std::make_shared<Block>(BLOCK_START_X, BLOCK_START_Y, type, color);

  color = (BlockColors)(random_color(engine));
  type = (BlockTypes)(random_type(engine));
  NextBlock = std::make_shared<Block>(NEXT_BLOCK_X, NEXT_BLOCK_Y, type, color);
}

void Game::Run(Controller const &controller,
               Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Game loop
  while (gameStatus != GameStatus::QUIT)
  {
    // Print game status
    //std::cout << "Game status: " << static_cast<std::underlying_type<GameStatus>::type>(gameStatus) << std::endl;

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(*this);

    /*
    game logic
     */
    Update();

    renderer.Render(*this);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// Update data
void Game::Update()
{
  if (gameStatus == GameStatus::RUNNING)
  {
    
  }
}

void Game::blockFall()
{
	static int GameBlock_down_counter = 0;
	
  static int Slide_counter = SLIDE_TIME;

	GameBlock_down_counter++;
	if (GameBlock_down_counter >= BlockSpeed)
	{
    std::vector<SDL_Point> positions = CurrentBlock.get()->GetMoveDownPositions();
		if (canChangeToPosition(positions))
		{
			CurrentBlock.get()->Move(Directions::DOWN);
			GameBlock_down_counter = 0;
		}
	}

	std::vector<SDL_Point> positions = CurrentBlock.get()->GetMoveDownPositions();
	if (!canChangeToPosition(positions))
	{
		Slide_counter--;
	}
	else
	{
		Slide_counter = SLIDE_TIME;
	}
	
	if (Slide_counter == 0)
	{
		Slide_counter = SLIDE_TIME;
	  finishCurrentBlock();
	}
}

void Game::finishCurrentBlock()
{
  Square** squares = CurrentBlock->GetSquares();
	for (int i=0; i<4; ++i)
	{
		Squares.push_back(std::make_shared(squares[i]));
	}

	createNewBlock();

	int completeNums = calcCompleteRows();

	if (completeNums > 0)
	{
		score += SCORE_PRE_LINE * completeNums;
		// next level
    if (score >= level * SCORE_PRE_LEVEL)
		{
			level++;
			BlockSpeed -= SPEED_CHANGE;
		}
	}

	// is Fail?

}


int Game::calcCompleteRows()
{
	int bottomLine = GAME_AREA_BOTTOM - SQUARES_MEDIAN;
	int topLine = SQUARES_MEDIAN;
	
  int rowSize = SQUARES_MEDIAN * 2;
	
  int squares_per_row[SQUARES_ROWS];
	
	int row = 0, completeRows = 0;

	// calculate how many squares in eash row
	for (int i=0; i< Squares.size(); ++i)
	{
		int center_y = Squares[i]->getCenter_y();
		row = (center_y - topLine) / rowSize;
		squares_per_row[row]++;
	}

	// Erase any full lines
	for (int line=0; line<SQUARES_ROWS; ++line)
	{
		if (squares_per_row[line] == SQUARES_PER_ROW)  // is full
		{
			completeRows++;
			for (int i=0; i< Squares.size(); ++i)
			{
				if (((Squares[i]->getCenter_y() - topLine) / rowSize) == line)
				{
					delete Squares[i].reset;
					Squares.erase( Squares.begin() + i);
					i--;
				}
			}
		}
	}
  // move the sqares
	for (int i=0; i< Squares.size(); ++i)
	{
		for (int line=0; line<21; ++line)
		{
			if (squares_per_row[line] == SQUARES_PER_ROW)
			{
				int y = Squares[i]->getCenter_y();
				row = (y - topLine) / rowSize;
				if (line > row)
				{
					Squares[i]->Move(Directions::DOWN);
				}
			}
		}
	}

	return completeRows;
}

void Game::createNewBlock()
{
	CurrentBlock = NextBlock;
	CurrentBlock->SetupBlock(BLOCK_START_X, BLOCK_START_Y, NextBlock->getBlockColor());

  auto color = (BlockColors)(random_color(engine));
  auto type = (BlockTypes)(random_type(engine));
  NextBlock = std::make_shared<Block>(NEXT_BLOCK_X, NEXT_BLOCK_Y, type, color);
}

bool Game::canChangeToPosition(std::vector<SDL_Point> & positions)
{
	for (int i=0; i<4; ++i)
	{
		if (positions[i].x < GAME_AREA_LEFT || positions[i].x > GAME_AREA_RIGHT)
		{
			return false;
		}
		
    if (positions[i].y > GAME_AREA_BOTTOM)
		{
			return false;
		}
	
  	for (int j=0; j< Squares.size(); ++j)
		{
			if ((abs(positions[i].x - Squares[j]->getCenter_x()) < SQUARES_SIZE) ||
				(abs(positions[i].y - Squares[j]->getCenter_y()) < SQUARES_SIZE))
			{
				return false;
			}
		}
	}
	return true;
}

void Game::SetBlockHorizontalSpeed()
{
  return;
}

void Game::RotateBlock()
{
  return;
}
void Game::SpeedUpBlockVertical(bool flag)
{
  return;
}
void Game::Pause()
{
  return;
}
void Game::Resume()
{
  return;
}

void Game::Quit()
{
  std::cout << "Game quit!\n";
  gameStatus = GameStatus::QUIT;
}

int Game::GetScore() const { return score; }

int Game::GetLevel() const { return level; }
