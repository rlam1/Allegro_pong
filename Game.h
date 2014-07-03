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
            
            paddle0->update();
            paddle1->update();

            // TODO: FINISH THIS LOGIC!!!!!!!!!!!
            if (checkBallCollision(ballCenter, ballSize, ballHitboxFactor, paddleCenter[0], paddleSize, paddleHBfactor))
            {
                ball->setStatus(HIT_PADDLE);
            }

            //if (checkBallCollision(ballCenter, ballSize, ballHitboxFactor, paddleCenter[1], paddleSize, paddleHBfactor))
            //{
            //    ball->setStatus(HIT_PADDLE);
            //}

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

        bool checkBallCollision(Point<float> ballXY, Point<int> ballHW, float ballHitboxF,
            Point<float> paddleXY, Point<int> paddleHW, float paddleHitboxf)
        {
            if ((ballXY.x - ballHW.x / ballHitboxF) + (ballXY.x + ballHW.x / ballHitboxF) <= paddleXY.x - paddleHW.x / paddleHitboxf
                || ballXY.x - ballHW.x / ballHitboxF >= (paddleXY.x - paddleHW.x / paddleHitboxf) + (paddleXY.x + paddleHW.x / paddleHitboxf))
                return false;

            if ((ballXY.y - ballHW.y / ballHitboxF) + (ballXY.y + ballHW.y / ballHitboxF) <= paddleXY.y - paddleHW.y / paddleHitboxf
                || ballXY.y - ballHW.y / ballHitboxF >= (paddleXY.x - paddleHW.y / paddleHitboxf) + (paddleXY.y + paddleHW.y / paddleHitboxf))
                return false;

            return true;
        }

        int score[2];
};