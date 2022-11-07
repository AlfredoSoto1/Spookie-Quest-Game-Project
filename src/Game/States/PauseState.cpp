#include "PauseState.h"
#include "ofMain.h"

PauseState::PauseState() {
    this->setCurrentState(CurrentState::PAUSED);
}

void PauseState::update() {

}

void PauseState::draw() {
    ofSetBackgroundColor(ofColor::black); 
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