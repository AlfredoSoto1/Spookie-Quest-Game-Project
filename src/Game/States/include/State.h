#pragma once

#include "ofMain.h"

enum CurrentState {
    TITLE,
    OVERWORLD,
    BATTLE,
    WIN,
    END,
    PAUSED,

    NONE
};

class State {
public:
    State() {}
    virtual ~State() {}
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    virtual void keyPressed(int key){}
    virtual void keyReleased(int key){}
    virtual void mousePressed(int x, int y, int button){}

    void mouseMoved(int x, int y){}
    void mouseExited(int x, int y){}
    void mouseEntered(int x, int y){}
    void mouseDragged(int x, int y, int button){}
    void mouseReleased(int x, int y, int button){}
    
    void windowResized(int w, int h){}
    void gotMessage(ofMessage msg){}
    void dragEvent(ofDragInfo dragInfo){}
    
    void setFinished(bool finished);
    // void setNextState(string nextState);
    void setNextState(int nextState);
    
    bool hasFinished();
    
    int getNextState();
    // string getNextState();

    void toggleMusic();
protected:
    int nextState;
    // string nextState;
    ofSoundPlayer music;
    bool finished = false;
};