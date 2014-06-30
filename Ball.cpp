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
    checkForCollisions();

    x += accelX;
    y += accelY;

    if (testBit(DEAD))
    {
        reset();
        clearBit(DEAD);
    }

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

void Ball::checkForCollisions()
{
    if (x - w / hitboxFactor < 0 || x + w / hitboxFactor > displayW)
    {
        accelX *= -1;
    }
    if (y - h / hitboxFactor < 0 || y + h / hitboxFactor > displayH)
    {
        accelY *= -1;
    }
}