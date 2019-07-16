#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput() const
{
  SDL_Event e;

  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      quitGame();
    }
    else if (e.type == SDL_KEYUP)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_DOWN:
        break;

      case SDLK_LEFT:
        break;

      case SDLK_RIGHT:
        break;
      }
    }
     else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_DOWN:

        break;

      case SDLK_LEFT:
        break;

      case SDLK_RIGHT:
        break;
      }
    }
  }
}

void Controller::setBlockHorizontalSpeed() const
{
  return;
}

void Controller::rotateBlock() const
{
  return;
}
void Controller::speedUpBlockVertical(bool flag) const
{
  return;
}
void Controller::pauseGame() const
{
  return;
}
void Controller::resumeGame() const
{
  return;
}

void Controller::quitGame() const
{
  return;
}