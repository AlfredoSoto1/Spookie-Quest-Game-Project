#pragma once

#include "Area.h"
#include "Enemy.h"
#include "Friend.h"
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

    bool hud = false;

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
    ofImage overworldEffectImage;
    ofImage overWorldAreaCollider;
    OverworldCamera *camera;

    bool friendInteract;
    bool debugMapCollider;
    bool bossNear;
};