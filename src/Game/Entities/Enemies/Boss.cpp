#include "Boss.h"
#include "OverworldCamera.h"

Boss::Boss(const string& name, int health, int baseDamage, int ox, int oy)
    :   Enemy(name, health, baseDamage, ox, oy)
{

}

Boss::~Boss() {
    
}

// void Boss::inOverworldUpdate() {

// }

// void Boss::fightingUpdate() {

// }

// void Boss::inOverworldDraw(void* camera) {

// }
