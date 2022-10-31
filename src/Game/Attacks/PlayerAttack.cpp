#include "PlayerAttack.h"

PlayerAttack::PlayerAttack() {
    //load button
    buttonAttack.load("images/ui/buttons/rock.png");
    currentAttack = 0;
}

int PlayerAttack::getNumberOfAttacks() {
    return attacks.size();
}

int PlayerAttack::getCurrentAttack() {
    return currentAttack;
}

void PlayerAttack::setCurrentAttack(int currentAttack) {
    if (currentAttack == -1)
        currentAttack = (int)(attacks.size() - 1);
    else if(currentAttack == (int)attacks.size())
        currentAttack = 0;
    this->currentAttack = currentAttack;
}

void PlayerAttack::addAttack(const Attack& attack) {
    this->attacks.push_back(attack);
}

void PlayerAttack::drawAttackList() {
    
    /*
        Draw Button for attacks depending how much the player has
    */

    int leftX = ofGetWidth() / 2 - (int)(buttonAttack.getWidth() * attacks.size() / 2);
    for(unsigned int i = 0; i < attacks.size(); i++) {
        if(currentAttack == (int)i)
            ofSetColor(255, 255, 255);
        else
            ofSetColor(180, 180, 180);
        buttonAttack.draw(leftX + i * buttonAttack.getWidth(), ofGetHeight() - buttonAttack.getHeight(), buttonAttack.getWidth(), buttonAttack.getWidth());
    }

    ofSetColor(255, 255, 255);//go back to full brightness
}