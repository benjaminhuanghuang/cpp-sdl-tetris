#include <iostream>
#include <string>
#include <stdio.h>

#include "renderer.h"
#include "constants.h"
#include "game.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width,
                   const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Init font
  TTF_Init();
  if (TTF_Init() == -1)
  {
    std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
  }
  font = TTF_OpenFont("res/regular.ttf", 20);
  if (font == nullptr)
  {
    std::cerr << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Game &game)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render game area
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

  // Render information area
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  // Render current Block and next block
  // CurrentBlock->DrawSquares(renderer);
  // NextBlock->DrawSquares(renderer);

  //-- Render blocks
  // for (int i=0; i<GameSquares.size(); ++i)
  // {
  // 	GameSquares[i]->DrawToRenderer(renderer);
  // }

  //-- Render infromation
  char nex_square[50];
  sprintf(nex_square, "NEXT SQUARE:");
  draw_text(nex_square, NEXT_BLOCK_X - 95, (NEXT_BLOCK_Y - 115));

  char cur_score[50];
  sprintf(cur_score, "CURRENT SCORE: %d", game.GetScore());
  draw_text(cur_score, SCORE_POSITION_X, SCORE_POSITION_Y);

  char cur_level[50];
  sprintf(cur_level, "CURRENT LEVEL: %d", game.GetLevel());
  draw_text(cur_level, LEVEL_POSITION_X, LEVEL_POSITION_Y);

  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int fps)
{
  std::string title{"Teris: FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::draw_text(std::string message, int x, int y)
{
  SDL_Color color = {255, 255, 255};
  SDL_Surface *surface = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);

  SDL_FreeSurface(surface);

  int width = 0, height = 0;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  SDL_Rect rect = {x, y, width, height};
  // Render to screen
  SDL_RenderCopy(sdl_renderer, texture, NULL, &rect);
}