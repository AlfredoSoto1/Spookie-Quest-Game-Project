#pragma once

#include "Area.h"
#include "Enemy.h"
#include "OverworldCamera.h"
#include "Player.h"
#include "State.h"

class OverworldState : public State {
public:
    OverworldState(Player *player, Area *area);

    Area* getArea();
    Player* getPlayer();
    Enemy* getEnemyToBattle();
    
    void loadArea(Area *Area);
    void setEnemy(Enemy *enemyToBattle);

    void draw();
    void update();
    

    void keyPressed(int key);
    void keyReleased(int key);
    
    void reset();



private:
    Area *area;
    Player *player;
    Enemy *enemyToBattle;
    ofImage overworldImage;
    OverworldCamera *camera;
};