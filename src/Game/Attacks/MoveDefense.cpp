#include "MoveDefense.h"

MoveDefense::MoveDefense() {
    defenseChoice = 0;
}

int MoveDefense::getNumberOfDefenses() {
    return defenses.size();
}

int MoveDefense::getDefenseChoice() {
    return defenseChoice;
}

void MoveDefense::setDefenseChoice(int defenseChoice) {
    if (defenseChoice == -1)
        defenseChoice = (int)(defenses.size() - 1);
    else if(defenseChoice == (int)defenses.size())
        defenseChoice = 0;
    this->defenseChoice = defenseChoice;
}

Defense& MoveDefense::getDefenses(int choice) {
    return defenses[choice];
}
void MoveDefense::addDefenses(const Defense& defense) {
    defenses.push_back(defense);
}