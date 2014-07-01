#include "Paddle.h"

int Paddle::numOfPaddles = 0;

void Paddle::update()
{
    al_get_mouse_state(&mouseState);
    mouseY = al_get_mouse_state_axis(&mouseState, 1);

    setPosition(x, mouseY);
}

void Paddle::reset()
{
    al_get_mouse_state(&mouseState);
    mouseY = al_get_mouse_state_axis(&mouseState, 1);

    setPosition(x, mouseY);
}
