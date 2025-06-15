#include <SDL3/SDL.h>
#include "player.h"

void player_init(Player *p) {
  p->x = 100.0f;
  p->y = 100.0f;
  p->vx = 0.0f;
  p->vy = 0.0f;
  p->w = 32;
  p->h = 32;
}

void player_update(Player *p, float delta_time, const bool *keys) {
  const float accel = 10.0f;
  const float movement_speed = 200.0f;

  // movement_speed has to be multiplied by delta_time in order to avoid weird behavior such as not being able to move right. 
  if (keys[SDL_SCANCODE_RIGHT]) {
    p->vx += accel;
    if (p->vx > movement_speed) p->vx = movement_speed;
  } else if (keys[SDL_SCANCODE_LEFT]) {
    p->vx -= accel;
    if (p->vx < -movement_speed) p->vx = -movement_speed;
  } else {
    if (p->vx > 0) {
      p->vx -= accel;
    }
    if (p->vx < 0) {
      p->vx += accel;
      if (p->vx > 0) p->vx = 0;
    }
  }

  p->x += p->vx * delta_time;
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