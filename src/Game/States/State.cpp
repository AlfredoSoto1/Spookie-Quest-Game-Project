#include "State.h"

bool State::hasFinished() {
    return finished;    
}

int State::getNextState() {
    return nextState;
}

CurrentState State::getCurrentState() {
    return currentState;
}

State* State::getPastState() {
    return pastRef;
}

void State::setFinished(bool finished) {
    this->finished = finished;
}

void State::setNextState(int nextState) {
    this->nextState = nextState;
}

void State::setCurrentState(CurrentState currentState) {
    this->currentState = currentState;
}

void State::setPastState(State* pastRef) {
    this->pastRef = pastRef;
}

// void State::setNextState(string nextState) {
//     this->nextState = nextState;
// }

void State::toggleMusic() {
    // No music to play
    if (!music.isLoaded()) return;
    music.isPlaying() ? music.stop() : music.play();
}