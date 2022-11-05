// #pragma once

// #ifndef BOSS_HEADER
// #define BOSS_HEADER

// #include "Animation.h"
// #include "EntityFighter.h"

// class Boss : public EntityFighter {
// public:
//     Boss(const string& name, int health, int baseDamage, int ox, int oy);
//     ~Boss();

//     bool isDead();
//     void kill();
//     void revive();
    
//     string getId();
//     ofImage getSprite();

//     void inOverworldUpdate();
//     void fightingUpdate();
//     void inOverworldDraw(void* camera) override;

// private:
//     string entityName;
    
//     int attackPhases;
//     int* healthPhases;

//     int renderX = 1000;
//     int renderY = 1000;

//     bool dead = false;
//     bool walking = false;

//     Animation *walkUp;
//     Animation *walkDown;
//     Animation *walkLeft;
//     Animation *walkRight;
//     Animation *fighting;

// // Boss: Implement a Boss class. This class must inherit from the Enemy
// // class. Bosses appear in an Area after all other Enemies of that area are
// // defeated. A Boss Battle must have at least two phases. That is to say, you
// // must deplete the Boss’s health bar twice in order to beat them. Defeating
// // a Boss moves the Player to the next Area or a Win State if there are no
// // remaining Areas. You must have at least one Boss instance per Area of
// // the game

// };

// #endif