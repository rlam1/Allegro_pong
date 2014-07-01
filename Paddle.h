#pragma once

#include "Object.h"

class Paddle : public Object
{
    public:
        Paddle(float X_, float Y_, int W_, int H_, int status_, std::string sprite)
            : Object(X_, Y_, W_, H_, 0.0, 0.0, status_, 1.5, sprite)
        {
            getDisplayData();

            reset();
        }

        virtual void reset() override;
        virtual void update() override;

    private:
        int mouseY;
        ALLEGRO_MOUSE_STATE mouseState;

        static int numOfPaddles;
};