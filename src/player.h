#include <SDL3/SDL.h>
const float delta_time;

typedef struct {
  int x, y;
  int vx, vy;
  int w, h;
} Player;

void player_init(Player *p) {
  // at the moment these values don't do anything
  const int movement_speed = 20;
  const int accel = 10;

  p->x = 100;
  p->y = 100;
  p->vx = 0;
  p->vy = 0;
  p->w = 32;
  p->h = 32;
}

void player_update(Player *p, float delta_time) {
  // stub
}

void player_draw(Player *p, SDL_Renderer *renderer) {
  SDL_FRect rect;

    rect.x = p->x;
    rect.y = p->y;
    rect.w = p->w;
    rect.h = p->h;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
    SDL_RenderRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
  
}