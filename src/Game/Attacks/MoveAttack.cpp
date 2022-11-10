#include "MoveAttack.h"

MoveAttack::MoveAttack() {
    attackChoice = 0;
}

int MoveAttack::getNumberOfAttacks() {
    return attacks.size();
}

int MoveAttack::getAttackChoice() {
    return attackChoice;
}

void MoveAttack::setAttackChoice(int attackChoice) {
    if (attackChoice == -1)
        attackChoice = (int)(attacks.size() - 1);
    else if(attackChoice == (int)attacks.size())
        attackChoice = 0;
    this->attackChoice = attackChoice;
}

Attack& MoveAttack::getAttack(int choice) {
    return attacks[choice];
}

void MoveAttack::addAttack(const Attack& attack) {
    this->attacks.push_back(attack);
}

vector<Attack>& MoveAttack::getAttacks() {
    return attacks;
}