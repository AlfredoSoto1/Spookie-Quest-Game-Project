#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "Area.h"

class BattleState : public State {
public:
    BattleState(Player *player, Area *area);
    void update();
    void draw();
    void startBattle(Enemy *enemy);
    void setEnemy(Enemy *enemy) {this-> enemy = enemy;};
    Enemy* getEnemy() {return enemy;};
    void setStage(ofImage stage) {this-> stage = stage;};
    void keyPressed(int key);
    void reset();

private: 
    ofImage stage;
    Player *player;
    Enemy *enemy;
    ofSoundPlayer buttonChange;
    ofSoundPlayer buttonSelect;
    ofImage button1;
    ofImage button2;
    ofImage button3;
    ofImage result1;
    ofImage result2;
    ofImage result3;
    int enemyChoice = 0;
    int currentButton;
    int currentPlayerHealth;
    int currentEnemyHealth;
    int resultTimer;
    bool canInteract;
    bool isAttacking;
    bool enemyHasChosenAttack;
    int PLAYER_MAX_HP;
};