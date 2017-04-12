//
// Created by Zachary Ingram on 4/3/17.
//

#ifndef BOUNCER_CONST_H
#define BOUNCER_CONST_H

// Screen dimensions
#define SCR_W 1024
#define SCR_H 576
#define IMG_SCALE 4

// Types for functions
// controls wrapper
typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool reload;
    bool newtext;
} cont;

// Dog wrapper
typedef struct {
    double x,y,xv,yv;
    bool onGround;
} d_t;

// Movement modifications
// dog
#define D_WALK_SPEED .7
#define D_CWALK_SPEED .3
#define D_WALK_J -3
#define D_JUMP_MAX -12
#define D_JUMP_MIN -6

// general
#define GRAVITY .5
#define RESISTANCE .75

// Tiles (to reduce calculations/frame)
#define TILE_DIM 64
#define LEVEL_W 50


#define DOG_W 44

#endif //BOUNCER_CONST_H
