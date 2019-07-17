## Setup cmake for sdl, sdl_ttf, sdl_image
  We need some CMake scripts for finding the SDL2, SDL2_image and SDL2_ttf libraries and headers.
  And tell CMake where to find them, via the CMAKE_MODULE_PATH variable. For example, if you put them in a subdirectory called cmake, then in your root CMakeLists.txt add the line
```
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
```
${PROJECT_SOURCE_DIR} is the root folder of the project

https://github.com/tcbrindle/sdl2-cmake-scripts

## Set window title
```
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
```

## Draw test with font
```
  SDL_Color color = {255, 255, 255};
  
  SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface); 
  SDL_FreeSurface(surface);

  int width = 0, height = 0;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  SDL_Rect rect = {x, y, width, height};

  // Render to screen
  SDL_RenderCopy(sdl_renderer, texture, NULL, &rect);
```

## Draw rectangle
```
  SDL_Rect block;
  block.x = x;
  block.y = y;
  block.w = width;
  block.h = height;

  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); // orange

  SDL_RenderFillRect(sdl_renderer, &block);
```

## Draw picture
```
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
```

