#include "Animation.h"

Animation::Animation(int speed, std::vector<ofImage> frames) {
    this->speed = speed;
    this->frames = frames;
    this->index = this->timer = 0;
    this->showOnce = false;
    this->endedAnimation = false;
}

void Animation::reset() {
    endedAnimation = false;
}

bool Animation::hasEnded() {
    return endedAnimation;
}

void Animation::setShowOnce(bool showOnce) {
    this->showOnce = showOnce;
    if(!showOnce)
        endedAnimation = false;
}

void Animation::resetTime() {
    timer = 0;
}

void Animation::update() {
    if (++timer > speed && !endedAnimation) {
        if (++index == frames.size()) {
            index = 0;
            if(showOnce) {
                endedAnimation = true;
            }
        }
        timer = 0;
    }
}

ofImage Animation::getCurrentFrame() {
    return frames[index];
}