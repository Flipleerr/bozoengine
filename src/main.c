#include <SDL3/SDL.h>

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("bozoengine", 800, 600, 0);
  if (!window) {
    printf("failed to create window.");
    return 1;
  }
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    // do nothing???
  }
  SDL_Delay(7000);

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
