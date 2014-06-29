#pragma once

#include <random>
#include <ctime>

#include "Object.h"

class Ball : public Object
{
    public:
        Ball(float X_, float Y_, int W_, int H_, int status_, std::string sprite)
            : Object(X_, Y_, W_, H_, 8.0, 8.0, status_, sprite)
        {
            std::srand(std::time(NULL));
            getDisplayData();
            randomDirection();
        }

        ~Ball() {}

        virtual void reset() override;
        virtual void update() override;

    private:
        const float ACCELERATION = 8.0;

        int displayW, displayH;

        void randomDirection();
        void getDisplayData();
};