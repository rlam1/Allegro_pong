#pragma once

// This class is responsible for connectiong all other classes derived from Object.
// It reads the state of the classes and uses some logic to decide the new state of
// them (gameplay). It is also responsible for handling drawing and deletion of the
// classes it connects.

#include <iostream>
#include <vector>
#include <string>

#include "Object.h"
#include "Ball.h"
#include "Paddle.h"

class Game 
{
    public:
        Game() {}
        virtual ~Game();

        void update();
        void draw();
        void addObject(Object *object);

    private:
        std::vector<Object*> objects;
        int score[2];

        bool checkBallCollision(Point<float> ballXY, Point<int> ballHW, float ballHitboxF,
            Point<float> paddleXY, Point<int> paddleHW, float paddleHitboxf);
};