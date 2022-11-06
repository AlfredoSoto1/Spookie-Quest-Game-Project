#include "Boss.h"
#include "OverworldCamera.h"

Boss::Boss(const string& name, int health, int baseDamage, int phases, int ox, int oy)
    :   Enemy(name, health, baseDamage, ox, oy)
{
    this->phases = phases;
}

Boss::~Boss() {
    
}

int Boss::getPhases() {
    return phases;
}

// void Boss::inOverworldUpdate() {

// }

// void Boss::fightingUpdate() {

// }

// void Boss::inOverworldDraw(void* camera) {

// }
