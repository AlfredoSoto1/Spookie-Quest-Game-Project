#include "EndGameState.h"

EndGameState::EndGameState() {
    this->setCurrentState(CurrentState::END);
    loseScreen.load("images/ui/gameover.png");
    winScreen.load("images/ui/winscreen.png");
    win = false;
}

void EndGameState::update() {
}

void EndGameState::draw() {
    if (win)
        winScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
    else
        loseScreen.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        loseScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void EndGameState::keyPressed(int key) {
    // setNextState("Title");
    setNextState(CurrentState::TITLE);
    setFinished(true);
}

void EndGameState::reset() {
    setFinished(false);
    // setNextState("");
    setNextState(CurrentState::NONE);
}