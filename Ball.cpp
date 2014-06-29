#include "Ball.h"

void Ball::reset()
{
    float resetX, resetY;

    resetX = displayW / 2.0;
    resetY = rand() % displayH;

    randomDirection();

    setPosition(resetX, resetY);
}

void Ball::update()
{
    x += accelX;
    y += accelY;

    calcCenter();
}

void Ball::randomDirection()
{
    if (rand() % 2)
    {
        accelX *= -1;
    }
    if (rand() % 2)
    {
        accelY *= -1;
    }
}

void Ball::getDisplayData()
{
    ALLEGRO_DISPLAY *display = al_get_current_display();

    displayW = al_get_display_width(display);
    displayH = al_get_display_height(display);
}