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
  int GetScore() const { return score; };
  int GetLevel() const { return level; };

  void Start();
  void Pause();
  void Resume();
  void SetSpeedUp(bool val) { speedingUp = val; };
  void SetDrawGrid(bool val) { drawgrid = val; };
  void Quit();

  void SetBlockHorizontalSpeed();
  void RotateBlock();
  void MoveBlock(Directions dir);

  void SpeedUpBlockVertical(bool flag);
  bool GetDrawGrid() { return drawgrid; };
  GameStatus GetStatus() { return gameStatus; };

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

  void update();
  bool isPositionAvailable(std::vector<SDL_Point> &positions);
  int removeCompleteRows();
  void finishCurrentBlock();
  void createNewBlock();

  void printSquares();
  void printCurrentBlock();

  int score{0};
  int level{1};
  int blockDropFrames{FRAMES_PER_DROP};
  bool speedingUp{false};
  bool drawgrid{false};
};

#endif