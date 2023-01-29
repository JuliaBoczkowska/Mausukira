#ifndef CONSTANTS_H
#define CONSTANTS_H

/** Tiles are 16 px wide and 16 px tall */
#define TILE_SIZE 32
#define MAP_SIZE_X 32
#define MAP_SIZE_Y 32

#define MAP_SIZE (MAP_SIZE_X * MAP_SIZE_Y)
#define MAP_SIZE_X_WORLD_COORD (MAP_SIZE_X * TILE_SIZE)
#define MAP_SIZE_Y_WORLD_COORD (MAP_SIZE_Y * TILE_SIZE)

#define PI 3.14159265358979323846 /* pi */
#endif                            // CONSTANTS_H
