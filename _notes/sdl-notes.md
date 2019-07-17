## Set window title
```
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
```

https://github.com/tcbrindle/sdl2-cmake-scripts