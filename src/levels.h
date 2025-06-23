#pragma once

#define MAX_WIDTH 256
#define MAX_HEIGHT 128

typedef struct {
  int width;
  int height;
  int tiles[MAX_WIDTH * MAX_HEIGHT];
} Level;

int is_solid_tile(int tile);
int load_bozolevel(const char *path, Level *level);
void render_level(SDL_Renderer *renderer, Level *level);