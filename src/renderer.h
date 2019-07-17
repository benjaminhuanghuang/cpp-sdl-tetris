#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

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
  
  void draw_text(std::string message, int x, int y);

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif