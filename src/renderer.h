#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "enums.h"

// forward declarations to avoid include cycles
class Game;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, 
           const std::size_t screen_height,
           const std::size_t grid_width, 
           const std::size_t grid_height);
           
  ~Renderer();

  void Render(Game& game);
  void UpdateWindowTitle(int fps);

 private:
  SDL_Window* sdl_window;
  SDL_Renderer* sdl_renderer;
  TTF_Font* font;
  SDL_Texture* bg_game_area;	
	
  void draw_text(std::string message, int x, int y);

  void draw_rectangle(int x, int y, int width, int height);

  SDL_Texture* load_texture( std::string path );
  void draw_image(int x, int y, SDL_Texture* image);
  void draw_game_area_background();
  void draw_score_area_background();
  void draw_current_block(Game &game);
  void draw_square(int center_x, int center_y, BlockColors color);

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif