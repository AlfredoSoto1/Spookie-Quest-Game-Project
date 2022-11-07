#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(30);
    ofSetWindowTitle("PA2");
    ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, ofGetScreenHeight() / 2 - ofGetHeight()/2);
    
    player = new Player("User-1", 100, 25);
    stateMaster = new StateMaster(player);
}

//--------------------------------------------------------------
void ofApp::update() {
    stateMaster->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    stateMaster->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    stateMaster->getCurrentState().keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    stateMaster->getCurrentState().keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    stateMaster->getCurrentState().mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    stateMaster->getCurrentState().mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    stateMaster->getCurrentState().mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    stateMaster->getCurrentState().mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    stateMaster->getCurrentState().mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    stateMaster->getCurrentState().mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    stateMaster->getCurrentState().windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    stateMaster->getCurrentState().gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    stateMaster->getCurrentState().dragEvent(dragInfo);
}