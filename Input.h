#pragma once

#include <array>

class Input {
public:
    Input();
    ~Input();

    void update(bool val, int key);
    bool getState(int key);

private:
    std::array<bool, 227> inputDeck;
};

