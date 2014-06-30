#pragma once

#include <random>
#include <ctime>

#include "Object.h"

class Ball : public Object
{
    public:
        Ball(float X_, float Y_, int W_, int H_, float acceleration, int status_, std::string sprite)
            : Object(X_, Y_, W_, H_, acceleration, acceleration, status_, sprite)
        {
            ACCELERATION = acceleration;
            std::srand(std::time(NULL));
            getDisplayData();
            randomDirection();
        }

        ~Ball() {}

        virtual void reset() override;
        virtual void update() override;

    private:
        float ACCELERATION;

        void randomDirection();
        void checkForCollisions();
};