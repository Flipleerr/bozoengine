#include <SDL3/SDL.h>
#include "player.h"

void player_init(Player *p) {
  p->x = 100;
  p->y = 100;
  p->vx = 0;
  p->vy = 0;
  p->w = 32;
  p->h = 32;
}

void player_update(Player *p, float delta_time, const bool *keys) {
  // at the moment acceleration doesn't do anything
  const float accel = 10.0f * delta_time;
  const float movement_speed = 10.0f;
  SDL_Log("movement speed: %f", movement_speed);

  if (keys[SDL_SCANCODE_RIGHT]) {
    p->vx = movement_speed;
  } else if (keys[SDL_SCANCODE_LEFT]) {
    p->vx = -movement_speed;
  } else {
    p->vx = 0;
  }

  p->x += p->vx;
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