#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "Area.h"

class BattleState : public State {
public:
    BattleState(Player *player, Area *area);

    Enemy* getEnemy();
    
    void setEnemy(Enemy *enemy);
    void setStage(ofImage stage);
    
    void update();
    void draw();
    
    void startBattle(Enemy *enemy);
    
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

    ofImage displayAttack;
    ofImage displayDeath;
    
    int enemyChoice = 0;
    int currentButton;
    
    int resultTimer;

    bool canInteract;
    bool isAttacking;
    bool enemyHasChosenAttack;
    bool isEnemyOnAttack;
    bool hasDied;

    void reHeal();
};