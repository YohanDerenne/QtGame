#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define MAX_SPEED 10

// Condition for width : MAX_SPEED + BLOC_SIZE > PLAYER_WIDTH (for holes)
#define PLAYER_WIDTH 39
// Condition for height : BLOC_SIZE * 2 > PLAYER_WIDTH (for holes)
#define PLAYER_HEIGHT 90

#define MAP_HEIGHT 1000
#define MAP_WIDTH 10000

#define BLOC_SIZE 50

#define MAX_GRAVITY 5

#define FPS 60


#endif // CONFIGURATION_H
