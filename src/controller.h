#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "enums.h"

class Controller {
 public:
  void HandleInput() const;

 private:
  void setBlockHorizontalSpeed() const;
  void rotateBlock() const;
  void speedUpBlockVertical(bool flag) const;
  void pauseGame() const;
  void resumeGame() const;
  void quitGame() const;

};

#endif