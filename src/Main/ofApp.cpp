#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(30);
    ofSetWindowTitle("PA2");
    ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, ofGetScreenHeight() / 2 - ofGetHeight()/2);
    
    player = new Player("User-1", 500, 25);
    stateManager = new StateManager(player);
}

//--------------------------------------------------------------
void ofApp::update() {
    stateManager->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    stateManager->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    stateManager->getCurrentState().keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    stateManager->getCurrentState().keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    stateManager->getCurrentState().mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    stateManager->getCurrentState().mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    stateManager->getCurrentState().mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    stateManager->getCurrentState().mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    stateManager->getCurrentState().mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    stateManager->getCurrentState().mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    stateManager->getCurrentState().windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    stateManager->getCurrentState().gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    stateManager->getCurrentState().dragEvent(dragInfo);
}