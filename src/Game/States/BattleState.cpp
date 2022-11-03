#include "BattleState.h"
#include "Attack.h"
#include "Defense.h"

BattleState::BattleState(Player *player, Area *area) {
    stage = area->getStage();

    /*
        Battle Music 
        change depending of enemy
    */
    music.load("audio/battle.wav");
    music.setLoop(true);
    music.setVolume(0.25);

    /*
        Interact sounds
    */
    buttonChange.load("audio/ui/beep.mp3");
    buttonChange.setVolume(0.5);
    buttonSelect.load("audio/ui/boop.mp3");
    buttonSelect.setVolume(0.5);

    /*
        Interact images 
    */
    button1.load("images/ui/buttons/rock.png");
    button2.load("images/ui/buttons/paper.png");
    button3.load("images/ui/buttons/scissors.png");
    result1.load("images/ui/buttons/rock1.png");
    result2.load("images/ui/buttons/paper1.png");
    result3.load("images/ui/buttons/scissors1.png");

    /*
        default setup
    */
    this->player = player;
    currentButton = 1;
    resultTimer = 0;
    canInteract = true;
    isAttacking = false;
    enemyHasChosenAttack = false;
    currentPlayerHealth = PLAYER_MAX_HP = player->getHealth();
}

void BattleState::startBattle(Enemy *enemy) {
    this->enemy = enemy;
    currentEnemyHealth = enemy->getHealth();
    currentPlayerHealth = player->getHealth();
}

void BattleState::update() {
    if (canInteract) {
        if (currentPlayerHealth <= 0) {
            setNextState("End");
            setFinished(true);
            player->setHealth(currentPlayerHealth);
            return;
        } else if (currentEnemyHealth <= 0) {
            setNextState("Win");
            setFinished(true);
            player->setHealth(currentPlayerHealth);
            return;
        }
    }

    //update sprite animation
    player->fightingUpdate();
    enemy->fightingUpdate();

    if(isAttacking) {
        Attack& playerAttack = player->getAttack(player->getAttackChoice());
        playerAttack.provokeAttack(&currentEnemyHealth, 1);

        if(!enemyHasChosenAttack) {
            enemy->setAttackChoice(rand() % enemy->getNumberOfAttacks());
            enemyHasChosenAttack = true;
        }
        Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());
        if(!playerAttack.isOnCoolDown()) {
            enemyAttack.provokeAttack(&currentPlayerHealth, enemy->getBaseDamage());
        }

        if(!enemyAttack.isOnCoolDown() && !playerAttack.isOnCoolDown()) {
            enemyAttack.reset();
            playerAttack.reset();
            canInteract = true;
            isAttacking = false;
            enemyHasChosenAttack = false;
        }
    }
}

void BattleState::draw() {
    // render stage
    stage.draw(0, 0, ofGetWidth(), ofGetHeight());

    // render combatant sprites
    player->fightingDraw();
    enemy->fightingDraw();

    //draw healthBar from both enemy and player
    int centerXEnemy = enemy->getFightingHitBox().getX() + enemy->getFightingHitBox().getWidth() / 2 - 192 / 2;
    int centerXPlayer = player->getFightingHitBox().getX() + player->getFightingHitBox().getWidth() / 2 - 192 / 2;

    enemy->drawHealthBar(centerXEnemy, 64, 192, 25, currentEnemyHealth, enemy->getHealth());
    player->drawHealthBar(centerXPlayer, 64, 192, 25, currentPlayerHealth, PLAYER_MAX_HP);

    // drawOutcome();

    // render move buttons
    player->drawAttackList();

    ofSetColor(255, 255, 255);
}

void BattleState::drawOutcome() {

    /*
        Draws outcome after "attacking"
    */
    if (resultTimer > 1) {
        resultTimer--;
        float posY = 60 * 4;
        float pposX = 64 * 4;
        float eposX = 80 * 4;
        float dim = 64;

        switch (outcome) {
            case Outcome::win:
                ofSetColor(100, 255, 100);
                if (choice == Move::rock)
                    result1.draw(pposX, posY, dim, dim);
                if (choice == Move::paper)
                    result2.draw(pposX, posY, dim, dim);
                if (choice == Move::scissors)
                    result3.draw(pposX, posY, dim, dim);
                ofSetColor(255, 100, 100);
                if (enemyChoice == 1)
                    result1.draw(eposX, posY, dim, dim);
                if (enemyChoice == 2)
                    result2.draw(eposX, posY, dim, dim);
                if (enemyChoice == 3)
                    result3.draw(eposX, posY, dim, dim);
                break;
            case Outcome::lose:
                ofSetColor(255, 100, 100);
                if (choice == Move::rock)
                    result1.draw(pposX, posY, dim, dim);
                if (choice == Move::paper)
                    result2.draw(pposX, posY, dim, dim);
                if (choice == Move::scissors)
                    result3.draw(pposX, posY, dim, dim);
                ofSetColor(100, 255, 100);
                if (enemyChoice == 1)
                    result1.draw(eposX, posY, dim, dim);
                if (enemyChoice == 2)
                    result2.draw(eposX, posY, dim, dim);
                if (enemyChoice == 3)
                    result3.draw(eposX, posY, dim, dim);
                break;
            case Outcome::draw:
                ofSetColor(200, 200, 100);
                if (choice == Move::rock)
                    result1.draw(pposX, posY, dim, dim);
                if (choice == Move::paper)
                    result2.draw(pposX, posY, dim, dim);
                if (choice == Move::scissors)
                    result3.draw(pposX, posY, dim, dim);
                if (enemyChoice == 1)
                    result1.draw(eposX, posY, dim, dim);
                if (enemyChoice == 2)
                    result2.draw(eposX, posY, dim, dim);
                if (enemyChoice == 3)
                    result3.draw(eposX, posY, dim, dim);
                break;
        }
        ofSetColor(255, 255, 255);
    }
    if (resultTimer == 1) {
        canInteract = true;
        choice = Move::none;
        resultTimer--;
    }
}

void BattleState::keyPressed(int key) {
    /*
        change type of attack
        plus add sounds
    */
    if (canInteract) {
        if (key == OF_KEY_LEFT || key == 'a') {
            buttonChange.play();
            player->setAttackChoice(player->getAttackChoice() - 1);
        }
        if (key == OF_KEY_RIGHT || key == 'd') {
            buttonChange.play();
            player->setAttackChoice(player->getAttackChoice() + 1);
        }
        if (key == OF_KEY_RETURN) {
            buttonSelect.play();
            isAttacking = true;
            canInteract = false;
        }
    }
}

void BattleState::reset() {
    setFinished(false);
    setNextState("");
    currentPlayerHealth = player->getHealth();
}