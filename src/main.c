#include <SDL3/SDL.h>
#include <stdbool.h>
#include "player.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  
  // window and renderer creation, might be usurped into game.c in the future
  SDL_Window *window = SDL_CreateWindow("bozoengine", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) {
    SDL_Log("failed to create window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("failed to create renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // main event loop, might be usurped into game.c in the future
  bool running = true;
  SDL_Event event;

  while(running) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
        return SDL_APP_SUCCESS;
      }
    }
    SDL_RenderClear(renderer);
    
    // player and movement stuff
    float delta_time = SDL_GetTicks() / 1000.0f;

    Player player;
    player_init(&player);
    player_update(&player, delta_time);
    player_draw(&player, renderer);
  
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
