#include "State.h"

bool State::hasFinished() {
    return finished;    
}

int State::getNextState() {
    return nextState;
}

int State::getPastState() {
    return pastState;
}

// string State::getNextState() {
//     return nextState;
// }

void State::setFinished(bool finished) {
    this->finished = finished;
}

void State::setNextState(int nextState) {
    this->nextState = nextState;
}

void State::setPastState(int pastState) {
    this->pastState = pastState;
}

// void State::setNextState(string nextState) {
//     this->nextState = nextState;
// }

void State::toggleMusic() {
    // No music to play
    if (!music.isLoaded()) return;
    music.isPlaying() ? music.stop() : music.play();
}