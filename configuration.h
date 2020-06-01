#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define WINDOW_WIDTH 1900
#define WINDOW_HEIGHT 1080

#define MAX_SPEED 10

// Condition for width : MAX_SPEED + BLOC_SIZE > PLAYER_WIDTH (for holes)
#define PLAYER_WIDTH 39
// Condition for height : BLOC_SIZE * 2 > PLAYER_WIDTH (for holes)
#define PLAYER_HEIGHT 60

#define MAP_HEIGHT 1080
#define MAP_WIDTH 4000

#define CAMERA_LEFT 450
#define CAMERA_RIGHT 800

#define BLOC_SIZE 50

#define VIRUS_WIDTH 50
#define VIRUS_HEIGHT 50

#define GEL_WIDTH 30
#define GEL_HEIGHT 50

#define MASK_WIDTH 70
#define MASK_HEIGHT 50

#define LIFE_WIDTH 30
#define LIFE_HEIGHT 30

#define PROJ_HEIGHT 40
#define PROJ_WIDTH 40

#define FLAG_HEIGHT 300
#define FLAG_WIDTH 120

#define GRAVITY 9

#define FPS 60

#define TITLE "Virus Fighter"

#define BTN_GAP 50


#endif // CONFIGURATION_H
