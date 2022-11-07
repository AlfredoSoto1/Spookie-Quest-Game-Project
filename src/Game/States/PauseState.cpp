#include "PauseState.h"
#include "ofMain.h"

PauseState::PauseState() {

}



void PauseState::update() {

}



void PauseState::draw() {
    ofSetBackgroundColor(ofColor::black); 
    ofSetColor(ofColor::white);
}

void PauseState::keyPressed(int key) {
    if(key == OF_KEY_ESC) {
        setNextState(CurrentState::OVERWORLD);
        setFinished(true);
    }
}

void PauseState::reset() {
    setNextState(CurrentState::NONE);
    setFinished(false);
}