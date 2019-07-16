#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "enums.h"
#include "controller.h"
#include "renderer.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);

  void Run(Controller const &controller,
           Renderer &renderer,
           std::size_t target_frame_duration);

  int GetScore() const;
  
  void Start();
  void Pause();
  void Resume();
  void Quit();
  
  void SetBlockHorizontalSpeed();
  void RotateBlock();
  void SpeedUpBlockVertical(bool flag);
  
private:
  GameStatus gameStatus{GameStatus::PAUSED};
  

  std::random_device dev;
  // random number generator
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void Update();

};

#endif