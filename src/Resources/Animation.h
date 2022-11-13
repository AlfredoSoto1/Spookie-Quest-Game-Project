#pragma once

#include "ofMain.h"

class Animation {
   private:
    int speed;
    unsigned int index;
    int timer;
    std::vector<ofImage> frames;
    bool end = false;
    bool showOnce;
    bool endedAnimation;

   public:
    Animation(int speed, std::vector<ofImage> frames);
    void update();
    ofImage getCurrentFrame();
    void reset();
    void resetTime();

    bool hasEnded();
    void setShowOnce(bool showOnce);
};