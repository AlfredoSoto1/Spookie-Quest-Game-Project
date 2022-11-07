#include "PauseState.h"
#include "ofMain.h"

PauseState::PauseState() {

}



void PauseState::update() {

}



void PauseState::draw() {
    ofSetBackgroundColor(ofColor::black); 
    font.drawString("PAUSED",(ofGetWidth() - font.stringWidth("PAUSED"))/2, 100);
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


