#include <SDL3/SDL.h>
#pragma once
float delta_time;

typedef struct {
  int x, y;
  int vx, vy;
  int w, h;
} Player;

void player_init(Player *p);
void player_update(Player *p, float delta_time, const bool *keys);
void player_draw(Player *p, SDL_Renderer *renderer);