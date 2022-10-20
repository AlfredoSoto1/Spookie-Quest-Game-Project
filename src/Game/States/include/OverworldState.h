#pragma once

#include "Area.h"
#include "Enemy.h"
#include "OverworldCamera.h"
#include "Player.h"
#include "State.h"

class OverworldState : public State {
   private:
    ofImage overworldImage;
    Player *player;
    OverworldCamera *camera;
    Area *area;
    std::vector<Enemy *> enemies;
    Enemy *enemy;

   public:
    OverworldState(Player *player, Area *area);
    Player *getPlayer() { return player; };
    void setEnemy(Enemy *enemy) { this->enemy = enemy; };
    Enemy *getEnemy() { return enemy; };
    void loadArea(Area *Area);
    Area *getArea() { return area; };
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void reset();
};