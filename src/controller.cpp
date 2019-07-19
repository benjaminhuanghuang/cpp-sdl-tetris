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
    else if (e.type == SDL_KEYDOWN)
    {
      // SDL_KEYDOWN is keep firing when the key is down
      switch (e.key.keysym.sym)
      {
      case SDLK_DOWN:
        break;

      case SDLK_LEFT:
        game.MoveBlock(Directions::LEFT);
        break;

      case SDLK_RIGHT:
        game.MoveBlock(Directions::RIGHT);
        break;
        
      case SDLK_SPACE:
        game.RotateBlock();
        break;
      }
    }
  }
}
