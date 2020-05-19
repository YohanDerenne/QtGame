#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 720

#define MAX_SPEED 10

// Condition for width : MAX_SPEED + BLOC_SIZE > PLAYER_WIDTH (for holes)
#define PLAYER_WIDTH 39
// Condition for height : BLOC_SIZE * 2 > PLAYER_WIDTH (for holes)
#define PLAYER_HEIGHT 90

#define MAP_HEIGHT 720
#define MAP_WIDTH 10000

#define BLOC_SIZE 50

#define VIRUS_WIDTH 50
#define VIRUS_HEIGHT 50

#define GEL_WIDTH 50
#define GEL_HEIGHT 50

#define MASK_WIDTH 50
#define MASK_HEIGHT 50

#define LIFE_WIDTH 50
#define LIFE_HEIGHT 50

#define GRAVITY 9

#define FPS 60


#endif // CONFIGURATION_H
