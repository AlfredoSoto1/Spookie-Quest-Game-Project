#pragma once

#ifndef DEFENSE_MOVE_HEADER
#define DEFENSE_MOVE_HEADER

#include "Defense.h"

class MoveDefense {
public:
    MoveDefense();
    
    int getNumberOfDefenses();
    int getDefenseChoice();

    void setDefenseChoice(int defenseChoice);

    Defense& getDefenses(int choice);
    void addDefenses(const Defense& defense);

protected:
    int defenseChoice;
    vector<Defense> defenses;
};

#endif