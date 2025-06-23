#include <SDL3/SDL.h>
#include <stdbool.h>

#include "player.h"
#include "levels.h"

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

  Level level;

  if (load_bozolevel("assets/levels/tgz.bzl", &level) != 0) {
    SDL_Log("failed to load level!");
    return SDL_APP_FAILURE;
  }
  SDL_Log("level data parse test: %d x %d", level.width, level.height);

  // player initalization
  Player player;
  player_init(&player);

  Uint64 last_time = SDL_GetTicks();

  // main event loop, might be usurped into game.c in the future
  bool running = true;
  SDL_Event event;

  while(running) {
    Uint32 now = SDL_GetTicks();
    float delta_time = (now - last_time) / 1000.0f;
    last_time = now;

    // clamp delta time to reasonable values
    if (delta_time > 0.016f) delta_time = 0.016f;
    if (delta_time <= 0.0f) delta_time = 0.001f;

    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
        return SDL_APP_SUCCESS;
      }
    }

    const bool *keys = SDL_GetKeyboardState(NULL);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // movement stuff
    player_update(&player, delta_time, keys, &level);
    player_draw(&player, renderer);
    render_level(renderer, &level);
    SDL_RenderPresent(renderer);

    // note: please switch this out for proper vsync.
    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}