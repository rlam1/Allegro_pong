#pragma once

// An single MSVC int can hold up to 32 different flags
const int ER_ERROR = (1 << 0);
const int ER_INVALID_STATE = (1 << 1);
const int ER_BITMAP = (1 << 2);
const int STATIC = (1 << 3);
const int NOCOLLISION = (1 << 4);
const int HIDDEN = (1 << 5);
const int DEAD = (1 << 6);
const int HIT_PADDLE = (1 << 7);
const int ISATLAS = (1 << 8);
const int ISMEM_BITMAP = (1 << 9);
const int DRAW_HITBOX = (1 << 10);