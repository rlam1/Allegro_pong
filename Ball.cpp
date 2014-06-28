#include "Ball.h"

void Ball::reset()
{
    setPosition(512, 300);
}

void Ball::update()
{
    x += accelX;
    y += accelY;

    calcCenter();
}

void Ball::getDisplayData()
{
    ALLEGRO_DISPLAY *display = al_get_current_display();

    displayW = al_get_display_width(display);
    displayH = al_get_display_height(display);
}