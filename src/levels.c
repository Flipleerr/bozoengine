#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "levels.h"

int is_solid_tile(int tile) {
  return tile == 1;
}

int load_bozolevel(const char *path, Level *level) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "failed to open level file: %s\n", path);
    return 1;
  }

  char line[1024];
  int tile_index = 0;
  int in_tile_block= 0;

  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '\n' || line[0] == '#') continue;

    if (strncmp(line, "width", 5) == 0) {
      sscanf(line, "width %d;", &level->width);
      continue;
    }

    if (strncmp(line, "height", 6) == 0) {
      sscanf(line, "height %d;", &level->height);
      continue;
    }

    if (strstr(line, "tiles") != NULL) {
      in_tile_block = 1;
      continue;
    }

    char *trim = line;
    while (isspace(*trim)) trim++;

    if (strncmp(trim, "};", 2) == 0 || strncmp(trim, "}", 1) == 0) {
      in_tile_block = 0;
      continue;
    }

    char *token = strtok(line, " \t\n");
    while (token) {
      SDL_Log("parsing token: '%s'", token);
      if (tile_index >= MAX_WIDTH * MAX_HEIGHT) {
        fprintf(stderr, "too many tiles! number of tiles exceeds maximum set in levels.h\n");
        fclose(file);
        return 1;
      }

      level->tiles[tile_index++] = atoi(token);
      token = strtok(NULL, " \t\n");  // get the next token
    }
  }

  fclose(file);

  if (tile_index != level->width * level->height) {
    fprintf(stderr, "tile count mismatch: expected %d, got %d!\n",
    level->width * level->height, tile_index);
    return 1;
  }
  
  return 0;
}

void render_level(SDL_Renderer *renderer, Level *level) {
  const int tile_size = 32;

  for (int y = 0; y < level->height; y++) {
    for (int x = 0; x < level->width; x++) {
      int tile = level->tiles[y * level->width + x];

      SDL_FRect rect = {
        .x = x * tile_size,
        .y = y * tile_size,
        .w = tile_size,
        .h = tile_size
      };

      if (tile == 1) {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }
}