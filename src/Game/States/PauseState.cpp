#include "PauseState.h"
#include "ofMain.h"

PauseState::PauseState() {

}

void PauseState::update() {

}

void PauseState::draw() {
    ofSetColor(ofColor::red);
    ofDrawRectangle(0,0,100, 100);
    ofSetColor(ofColor::white);
}

void PauseState::keyPressed(int key) {
    if(key == OF_KEY_ESC) {
        setNextState("Overworld");
        setFinished(true);
    }
}

void PauseState::reset() {
    setNextState("");
    setFinished(false);
}
