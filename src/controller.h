#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "enums.h"
// #include "game.h"

class Controller {
 public:
  void HandleInput() const;

 private:
  //Game _game;
  void setBlockHorizontalSpeed() const;
  void rotateBlock() const;
  void speedUpBlockVertical(bool flag) const;
  void pauseGame() const;
  void resumeGame() const;
  void quitGame() const;
};

#endif