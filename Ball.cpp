#include "Ball.h"

void Ball::reset()
{
    float resetX, resetY;

    resetX = displayW / 2.0f;
    resetY = rand() % displayH;

    randomDirection();

    setPosition(resetX, resetY);
}

void Ball::update()
{
    checkForCollisions();

    x += accelX;
    y += accelY;

    if (x - w / hitboxFactor <= 0 || x + w / hitboxFactor >= displayW)
        setBit(DEAD);

    if (testBit(DEAD))
    {
        reset();
        clearBit(DEAD);
    }

    if (testBit(HIT_PADDLE))
    {
        reverseAcceleration();
        clearBit(HIT_PADDLE);
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