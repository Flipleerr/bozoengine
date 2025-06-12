#include <SDL3/SDL.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("bozoengine", 800, 600, 0);
  if (!window) {
    printf("failed to create window.");
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  bool running = true;
  SDL_Event event;

  while(running) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
