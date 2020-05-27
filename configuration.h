#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define WINDOW_WIDTH 1900
#define WINDOW_HEIGHT 1200

#define MAX_SPEED 10

// Condition for width : MAX_SPEED + BLOC_SIZE > PLAYER_WIDTH (for holes)
#define PLAYER_WIDTH 39
// Condition for height : BLOC_SIZE * 2 > PLAYER_WIDTH (for holes)
#define PLAYER_HEIGHT 60

#define MAP_HEIGHT 1200
#define MAP_WIDTH 4000

#define CAMERA_LEFT 350
#define CAMERA_RIGHT 700

#define BLOC_SIZE 50

#define VIRUS_WIDTH 50
#define VIRUS_HEIGHT 50

#define GRAVITY 9

#define FPS 60


#endif // CONFIGURATION_H
