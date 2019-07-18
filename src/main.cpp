#include <iostream>
#include <memory>
#include "constants.h"
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, kGridWidth, kGridHeight);
  Game game(kGridWidth, kGridHeight);
  Controller controller;
  
  game.Init();
  game.Run(controller, renderer, kMsPerFrame);
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}