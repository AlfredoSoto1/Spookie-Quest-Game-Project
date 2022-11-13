#include "Boss.h"
#include "OverworldCamera.h"

Boss::Boss(const string& name, int health, int baseDamage, int phases, int ox, int oy)
    :   Enemy(name, EnemyE::EVIL_WIZZARD, health, baseDamage, ox, oy)
{
    this->maxPhases = phases;
    this->currentPhase = 0;
    this->hasPassedNextPhase = false;
}

Boss::~Boss() {
    
}

int Boss::getPhasesCount() {
    return maxPhases;
}

int Boss::getCurrentPhase() {
    return currentPhase;
}

void Boss::reHeal() {
    health++;
    if(health > maxHealth) {
        health = maxHealth;
        hasPassedNextPhase = false;
    }
}

bool Boss::passToNextPhase() {
    if(health <= 0 && !hasPassedNextPhase){
        hasPassedNextPhase = true;
        currentPhase++;
        if(!hasPhasesLeft()) {
            currentPhase = maxPhases;
            return false;
        }
    }
    return hasPassedNextPhase;
}

bool Boss::hasPhasesLeft() {
    return currentPhase < maxPhases;
}

void Boss::reset() {
    currentPhase = 0;
    hasPassedNextPhase = false;
}
