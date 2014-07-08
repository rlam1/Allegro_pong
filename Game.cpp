#include "Game.h"

Game::Game()
{
    Object* paddle0 = nullptr;
    Object* paddle1 = nullptr;
    Object* ball = nullptr;
}

Game::~Game()
{
    for (auto &object : objects)
    {
        delete object;
    }
}

void Game::init()
{
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
}

void Game::update()
{
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

    if (checkBallCollision(ballCenter, ballSize, ballHitboxFactor, paddleCenter[1], paddleSize, paddleHBfactor))
    {
        ball->setStatus(HIT_PADDLE);
    }

    ball->update();
}

void Game::draw()
{
    for (auto &object : objects)
    {
        object->draw();
    }
}

void Game::addObject(Object *object)
{
    objects.push_back(object);
    object->reset();
}

bool Game::checkBallCollision(Point<float> ballXY, Point<int> ballHW, float ballHitboxF,
    Point<float> paddleXY, Point<int> paddleHW, float paddleHitboxF)
{
    float Ax1 = ballXY.x - ballHW.x / ballHitboxF;
    float Ax2 = ballXY.x + ballHW.x / ballHitboxF;
    float Ay1 = ballXY.y - ballHW.y / ballHitboxF;
    float Ay2 = ballXY.y + ballHW.y / ballHitboxF;

    float Bx1 = paddleXY.x - paddleHW.x / paddleHitboxF;
    float Bx2 = paddleXY.x + paddleHW.x / paddleHitboxF;
    float By1 = paddleXY.y - paddleHW.y / paddleHitboxF;
    float By2 = paddleXY.y + paddleHW.y / paddleHitboxF;
    
    return !(Ax2 < Bx1 || Bx2 < Ax1 || Ax2 < By1 || By2 < Ay1);
}