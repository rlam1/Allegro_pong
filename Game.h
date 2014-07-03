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

        virtual ~Game() 
        {
            for (auto &object : objects)
            {
                delete object;
            }
        }

        void update()
        {
            Object* paddle0 = nullptr;
            Object* paddle1 = nullptr;
            Object* ball = nullptr;

            for (auto &object : objects)
            {
                int name = object->getName();

                switch (name)
                {
                    case BALL:
                        ball = object;
                        break;
                    case PADDLE0:
                        paddle0 = object;
                        break;
                    case PADDLE1:
                        paddle1 = object;
                        break;
                    default:
#ifdef _DEBUG
                        std::cout << "Warning! A base Object instance is live!" << std::endl;
#endif
                        break;
                }
            }

            Point<float> ballCenter = ball->getCenter();
            Point<int> ballSize = ball->getSize();
            float ballHitboxFactor = ball->getHitboxFactor();

            Point<float> paddleCenter[2];
            paddleCenter[0] = paddle0->getCenter();
            paddleCenter[1] = paddle1->getCenter();
            Point<int> paddleSize = paddle0->getSize();
            float paddleHBfactor = paddle0->getHitboxFactor();

            // TODO: FINISH THIS LOGIC!!!!!!!!!!!

            if ((ballCenter.x - (ballSize.x / ballHitboxFactor)) <= (paddleCenter[0].x + (paddleSize.x / paddleHBfactor)))
            {
                ball->setStatus(DEAD);
            }
            
            paddle0->update();
            paddle1->update();

            if ((ball->getStatus() & DEAD) != 0)
            {
                ball->reset();
                ball->setStatus(!DEAD);
            }
            ball->update();
        }

        void draw()
        {
            for (auto &object : objects)
            {
                object->draw();
            }
        }

        void addObject(Object *object)
        {
            objects.push_back(object);
            object->reset();
        }

    private:
        std::vector<Object*> objects;

        int score[2];
};