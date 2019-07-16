#include "controller.h"
#include "game.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(Game &game) const
{
  SDL_Event e;

  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      game.Quit();
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

