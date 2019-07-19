#include <iostream>
#include <string>
#include <stdio.h>

#include "renderer.h"
#include "constants.h"
#include "game.h"
#include "square.h"
#include "block.h"

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
  if (TTF_Init() == -1)
  {
    std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
  }
  font = TTF_OpenFont("res/regular.ttf", 20);
  if (font == nullptr)
  {
    std::cerr << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
  }

  // Init image
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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

  bg_game_area = load_texture("res/bg1.png"); // need sdl_render
}

Renderer::~Renderer()
{
  // font
  TTF_CloseFont(font);
  TTF_Quit();

  // image
  SDL_DestroyTexture(bg_game_area);
  IMG_Quit();

  SDL_DestroyRenderer(sdl_renderer);
  // window
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
  draw_game_area_background();

  draw_current_block(game);

  //-- Render blocks
  // for (int i=0; i<GameSquares.size(); ++i)
  // {
  // 	GameSquares[i]->DrawToRenderer(renderer);
  // }

  // Render score area
  draw_score_area_background();

  draw_next_block(game);

  //-- Render infromation
  draw_text("NEXT SQUARE:", NEXT_BLOCK_X - 95, (NEXT_BLOCK_Y - 115));

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

SDL_Texture *Renderer::load_texture(std::string path)
{
  //The final texture
  SDL_Texture *newTexture = NULL;

  //Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(sdl_renderer, loadedSurface);
    if (newTexture == NULL)
    {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}

void Renderer::draw_rectangle(int x, int y, int width, int height)
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;

  SDL_RenderFillRect(sdl_renderer, &rect);
}

void Renderer::draw_game_area_background()
{
  draw_image(0, 0, bg_game_area);
}

void Renderer::draw_score_area_background()
{
  // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); // orange
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
  draw_rectangle(SCORE_AREA_LEFT, 0, SCORE_AREA_BOTTOM, SCORE_AREA_RIGHT);
}

void Renderer::draw_image(int x, int y, SDL_Texture *image)
{
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = GAME_AREA_RIGHT;
  rect.h = GAME_AREA_BOTTOM;

  SDL_RenderCopy(sdl_renderer, image, NULL, &rect);
}

void Renderer::draw_current_block(Game &game)
{
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); // orange

  std::shared_ptr<Block> block = game.CurrentBlock;
  Square **squares = block.get()->GetSquares();
  set_color(block.get()->getBlockColor());

  for (int i = 0; i < 4; ++i)
  {
    int center_x = squares[i]->getCenter_x();
    int center_y = squares[i]->getCenter_y();
    SDL_Rect rect = {
        center_x - SQUARES_MEDIAN + 1,
        center_y - SQUARES_MEDIAN + 1,
        SQUARES_MEDIAN * 2 - 2,
        SQUARES_MEDIAN * 2 - 2};
    SDL_RenderFillRect(sdl_renderer, &rect);
  }
}

void Renderer::draw_next_block(Game &game)
{
  std::shared_ptr<Block> block = game.NextBlock;
  
  Square **squares = block.get()->GetSquares();

  set_color(block.get()->getBlockColor());

  for (int i = 0; i < 4; ++i)
  {
    int center_x = squares[i]->getCenter_x();
    int center_y = squares[i]->getCenter_y();
    SDL_Rect rect = {
        center_x - SQUARES_MEDIAN + 1,
        center_y - SQUARES_MEDIAN + 1,
        SQUARES_MEDIAN * 2 - 2,
        SQUARES_MEDIAN * 2 - 2};
    SDL_RenderFillRect(sdl_renderer, &rect);
  }
}
void Renderer::set_color(BlockColors color)
{
  switch (color)
  {
  case BlockColors::Blue:
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
    break;
  case BlockColors::Orange:
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    break;
  case BlockColors::Gray:
    SDL_SetRenderDrawColor(sdl_renderer, 0xCC, 0xCC, 0xBB, 0xFF);
    break;
  case BlockColors::Green:
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xFF, 0xFF);
    break;
  default:
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);  // red
    break;
  }
}