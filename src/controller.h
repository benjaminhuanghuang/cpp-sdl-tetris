#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
// forward declarations to avoid include cycle
class Game;

class Controller
{
public:
  void HandleInput(Game& game) const;

private:

};

#endif