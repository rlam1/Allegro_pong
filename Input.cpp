#include "Input.h"

Input::Input()
{

    inputDeck.fill(false);

}


Input::~Input()
{
}

void Input::update(bool val, int key)
{
    inputDeck[key] = val;
}

bool Input::getState(int key)
{
    return inputDeck[key];
}
