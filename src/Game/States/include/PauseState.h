#pragma once

#include "State.h"
#include "Area.h"
#include "Player.h"

class PauseState : public State {
private:
    ofImage background;

public:
    PauseState();
    void update();
    void draw();
    void keyPressed(int key);
    void reset();
};