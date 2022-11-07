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

        setNextState(getPastState());
        setPastState(CurrentState::NONE);
        setFinished(true);
        
    }
}

void PauseState::reset() {
    setNextState(CurrentState::NONE);
    setPastState(CurrentState::NONE);
    setFinished(false);
}