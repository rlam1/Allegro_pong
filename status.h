#pragma once

// An single MSVC int can hold up to 32 different flags

enum {
	ERROR = (1 << 0),
	ER_INVALID_STATE = (1 << 1),
	ER_BITMAP = (1 << 2),
	STATIC = (1 << 3),
	NOCOLLISION = (1 << 4),
	HIDDEN = (1 << 5),
	DEAD = (1 << 6),
	
}