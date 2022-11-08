#include "Boss.h"
#include "OverworldCamera.h"

Boss::Boss(const string& name, int health, int baseDamage, int phases, int ox, int oy)
    :   Enemy(name, health, baseDamage, ox, oy)
{
    this->phases = phases;
    this->maxPhases = phases;
}

Boss::~Boss() {
    
}

void Boss::setCurrentPhases(int phases){
    this->phases = phases;
}

int Boss::getCurrentPhases(){
    return phases < 0 ? 0 : phases;
}

int Boss::getPhases() {
    return maxPhases;
}

// void Boss::inOverworldUpdate() {

// }

// void Boss::fightingUpdate() {

// }

// void Boss::inOverworldDraw(void* camera) {

// }
