#include "EndGameState.h"

EndGameState::EndGameState() {
    this->setCurrentState(CurrentState::END);
    loseScreen.load("images/ui/losescreen.png");
    winScreen.load("images/ui/winscreen.png");
    win = false;
}

void EndGameState::update() {
}

void EndGameState::draw() {
    if (win)
        winScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
    else
        loseScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void EndGameState::keyPressed(int key) {
    setNextState(CurrentState::TITLE);
    setFinished(true);
}

void EndGameState::reset() {
    setFinished(false);
    setNextState(CurrentState::NONE);
}