#include <SDL3/SDL.h>
#include "player.h"
#include "levels.h"

void player_init(Player *p) {
  p->x = 100.0f;
  p->y = 100.0f;
  p->vx = 0.0f;
  p->vy = 0.0f;
  p->w = 32;
  p->h = 32;
  p->on_ground = 0;
}

void player_update(Player *p, float delta_time, const bool *keys, Level *level) {
  const float accel = 50.0f;
  const float gravity = 10.0f;
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

  player_collision_check(p, level);

  if (!p->on_ground) {
    p->vy += gravity;
  }

  p->x += p->vx * delta_time;
  p->y += p->vy * delta_time;
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

void player_collision_check(Player *p, Level *level) {
  int tile_x = (int)(p->x) / 32;
  int tile_y = ((int)(p->y + p->h)) / 32;

  int idx = tile_y * level->width + tile_x;
  if (idx >= 0 && idx < level->width * level->height) {
    int tile = level->tiles[idx];
    if (is_solid_tile(tile)) {
      p->vy = 0;
      p->y = tile_y * 32 - p->h;
      p->on_ground = 1;
    }
    
    p->on_ground = 0;
  }
}