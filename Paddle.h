#pragma once

#include "Object.h"

class Paddle : public Object
{
    public:
        Paddle(float X_, float Y_, int W_, int H_, int status_, int name_, std::string sprite)
            : Object(X_, Y_, W_, H_, 0.0f, 0.0f, status_, 2.0f, sprite)
        {
            name = name_;

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