#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include <memory>
#include <SDL.h>
#include "enums.h"
#include "constants.h"
#include "controller.h"
#include "renderer.h"
#include "square.h"
#include "block.h"


class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);

  void Run(Controller const &controller,
           Renderer &renderer,
           std::size_t target_frame_duration);
  void Init();  
  int GetScore() const;
  int GetLevel() const;
  
  void Start();
  void Pause();
  void Resume();
  void Quit();
  
  void SetBlockHorizontalSpeed();
  void RotateBlock();
  void SpeedUpBlockVertical(bool flag);

  std::shared_ptr<Block> CurrentBlock;			
	std::shared_ptr<Block> NextBlock;				
	std::vector<std::shared_ptr<Square>> Squares;		
  
private:
  GameStatus gameStatus{GameStatus::PAUSED};
  

  std::random_device dev;
  // random number generator
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_color;
  std::uniform_int_distribution<int> random_type;

  bool isPositionAvailable(std::vector<SDL_Point> & positions);
  void blockFall();
  int  calcCompleteRows();
  void finishCurrentBlock();
  void createNewBlock();
  
  int score{0};
  int level{1};
  int blockSpeed{INITIAL_SPEED};

  void update();
};

#endif