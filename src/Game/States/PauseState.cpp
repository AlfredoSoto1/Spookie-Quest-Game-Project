#include "PauseState.h"
#include "ofMain.h"

PauseState::PauseState() {
    this->setCurrentState(CurrentState::PAUSED);
    background.load("images/PauseState/PAUSED.png");
}

void PauseState::update() {

}

void PauseState::draw() {
    // ofSetBackgroundColor(ofColor::black);
    background.draw(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
}

void PauseState::keyPressed(int key) {
    if(key == OF_KEY_ESC) {
        State* lastState = getPastState();
        setNextState(lastState->getCurrentState());
        setFinished(true);
    }
}

void PauseState::reset() {
    setNextState(CurrentState::NONE);
    setFinished(false);
}