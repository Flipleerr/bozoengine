#pragma once
#include <SDL3/SDL.h>
#include "levels.h"

float delta_time;

typedef struct {
  int x, y;
  int vx, vy;
  int w, h;
  int on_ground;
} Player;

void player_init(Player *p);
void player_update(Player *p, float delta_time, const bool *keys, Level *level);
void player_draw(Player *p, SDL_Renderer *renderer);
void player_collision_check(Player *p, Level *level);