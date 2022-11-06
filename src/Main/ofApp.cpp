#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(30);
    ofSetWindowTitle("PA2");
    ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, ofGetScreenHeight() / 2 - ofGetHeight()/2);
    
    // initAreas();

    //player creation
    player = new Player("User-1", 500, 15);
    stateManager = new StateManager(player);

    // Declaration and Initialization of States
    // titleState = new TitleState();
    // overworldState = new OverworldState(player, currentArea);
    // battleState = new BattleState(player, currentArea);
    // winState = new WinState();
    // endGameState = new EndGameState();

    // // Initial State
    // currentState = titleState;
}

//--------------------------------------------------------------
// void ofApp::initAreas() {

//     vector<Entity*> enemies2;
//     ofPoint entrancePosition2(4 * 110, 4 * 116);
//     Enemy *area2Enemy1 = new Enemy("enemy2", 30, 6, 4 * 120, 4 * 342);
//     Enemy *area2Enemy2 = new Enemy("enemy2", 30, 6, 4 * 254, 4 * 130);
//     Enemy *area2Enemy3 = new Enemy("enemy2", 30, 6, 4 * 542, 4 * 124);
//     Enemy *area2Enemy4 = new Enemy("enemy2", 30, 6, 4 * 532, 4 * 368);
//     Enemy *area2Enemy5 = new Enemy("enemy2", 30, 6, 4 * 266, 4 * 312);
//     Enemy *area2Enemy6 = new Enemy("enemy2", 30, 6, 4 * 194, 4 * 532);
//     enemies2.push_back(area2Enemy1);
//     enemies2.push_back(area2Enemy2);
//     enemies2.push_back(area2Enemy3);
//     enemies2.push_back(area2Enemy4);
//     enemies2.push_back(area2Enemy5);
//     enemies2.push_back(area2Enemy6);
//     area2 = new Area("Area2", NULL, "images/areas/area2.png", "audio/ice.wav", "images/stages/stage2.png", entrancePosition2, enemies2);

//     vector<Entity*> enemies1;
//     ofPoint entrancePosition1(4 * 414, 4 * 566);
//     Enemy *area1Enemy1 = new Enemy("enemy1", 20, 4, 4 * 480, 4 * 432);
//     // Enemy *area1Enemy2 = new Enemy("enemy1", 20, 4, 4 * 225, 4 * 178);
//     // Enemy *area1Enemy3 = new Enemy("enemy1", 20, 4, 4 * 420, 4 * 178);

//     enemies1.push_back(area1Enemy1);
//     // enemies1.push_back(area1Enemy2);
//     // enemies1.push_back(area1Enemy3);
    
//     Boss* bossLevel1 = new Boss("Boss-1", 20, 4, 1280, 720);
//     enemies1.push_back(bossLevel1);

//     Rock* rock = new Rock("rock-1", 4 * 480, 4 * 470, 1);
//     enemies1.push_back(rock);

//     area1 = new Area("Area1", area2, "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1);
//     currentArea = area1;
// }

//--------------------------------------------------------------
void ofApp::update() {
    stateManager->update();
    // currentState->update();
    // if (currentState->hasFinished()) {
    //     currentState->toggleMusic();
    //     if (currentState->getNextState() == "Title") {
    //         endGameState->setWin(false);
    //         area1->resetEnemies();
    //         area2->resetEnemies();
    //         currentArea = area1;
    //         battleState->reset();
    //         battleState->setStage(currentArea->getStage());
    //         overworldState->loadArea(currentArea);
    //         currentState = titleState;
    //     } else if (currentState->getNextState() == "Overworld") {
    //         currentState = overworldState;
    //     } else if (currentState->getNextState() == "Battle") {
    //         battleState->startBattle(overworldState->getEnemyToBattle());
    //         currentState = battleState;
    //     } else if (currentState->getNextState() == "Win") {
    //         Enemy* enemy = overworldState->getEnemyToBattle();
    //         enemy->kill();
    //         if (currentArea->getRemainingEnemies() == 0) {
    //             if (currentArea->getNextArea() == NULL) {
    //                 endGameState->setWin(true);
    //                 currentState = endGameState;
    //             } else {
    //                 currentArea = currentArea->getNextArea();
    //                 overworldState->loadArea(currentArea);
    //                 battleState->setStage(currentArea->getStage());
    //                 currentState = winState;
    //             }
    //         } else {
    //             currentState = winState;
    //         }
    //     } else if (currentState->getNextState() == "End"){
    //         currentState = endGameState;
    //         player->reset();
    //     }
    //     currentState->toggleMusic();
    //     currentState->reset();
    // }
}

//--------------------------------------------------------------
void ofApp::draw() {
    // currentState->draw();
    stateManager->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // currentState->keyPressed(key);
    stateManager->getCurrentState().keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    // currentState->keyReleased(key);
    stateManager->getCurrentState().keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    // currentState->mouseMoved(x, y);
    stateManager->getCurrentState().mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    // currentState->mouseDragged(x, y, button);
    stateManager->getCurrentState().mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // currentState->mousePressed(x, y, button);
    stateManager->getCurrentState().mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    // currentState->mouseReleased(x, y, button);
    stateManager->getCurrentState().mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    // currentState->mouseEntered(x, y);
    stateManager->getCurrentState().mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    // currentState->mouseExited(x, y);
    stateManager->getCurrentState().mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    // currentState->windowResized(w, h);
    stateManager->getCurrentState().windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    // currentState->gotMessage(msg);
    stateManager->getCurrentState().gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    // currentState->dragEvent(dragInfo);
    stateManager->getCurrentState().dragEvent(dragInfo);
}