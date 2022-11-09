#include "BattleState.h"
#include "Attack.h"
#include "Defense.h"

BattleState::BattleState(Player *player, Area *area) {
    this->setCurrentState(CurrentState::BATTLE);
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
    needsToReHeal = false;
    enemyHasChosenAttack = false;
}

Enemy* BattleState::getEnemy() {
    return enemy;
}

void BattleState::setEnemy(Enemy *enemy) {
    this->enemy = enemy;
}

void BattleState::setStage(ofImage stage) {
    this->stage = stage;
}

void BattleState::startBattle(Enemy *enemy) {
    this->enemy = enemy;
}

void BattleState::reHeal() {
    if(enemy->getHealth() > enemy->getMaxHealth()) {
        enemy->setHealth(enemy->getMaxHealth());
        needsToReHeal = false;
    } else if(needsToReHeal) {
        enemy->setHealth(enemy->getHealth() + 1);
    }
}

void BattleState::update() {
    if (canInteract) {
        if (player->getHealth() <= 0) {
            setNextState(CurrentState::END);
            setFinished(true);
            return;
        } else if (enemy->getHealth() <= 0 && !needsToReHeal) {
            Boss* boss = dynamic_cast<Boss*>(enemy);
            if(boss != nullptr){
                if(boss->getCurrentPhases() > 1) {
                    boss->setCurrentPhases(boss->getCurrentPhases() - 1);
                    needsToReHeal = true;
                    return;
                }
            }
            setNextState(CurrentState::WIN);
            setFinished(true);
            return;
        }
    }

    reHeal();

    //update sprite animation
    player->fightingUpdate();
    enemy->fightingUpdate();

    if(isAttacking) {

        //TODO
        //add defenses
        
        Attack& playerAttack = player->getAttack(player->getAttackChoice());
        int currentEnemyHealth = enemy->getHealth();
        playerAttack.provokeAttack(&currentEnemyHealth, 1);
        enemy->setHealth(currentEnemyHealth);

        if(!enemyHasChosenAttack) {
            enemy->setAttackChoice(rand() % enemy->getNumberOfAttacks());
            enemyHasChosenAttack = true;
        }
        Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());
        if(!playerAttack.isOnCoolDown()) {
            int currentPlayerHealth = player->getHealth();
            enemyAttack.provokeAttack(&currentPlayerHealth, enemy->getBaseDamage());
            player->setHealth(currentPlayerHealth);
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
    int healthBarWidth = 256;
    int centerXEnemy = enemy->getFightingHitBox().getX() + enemy->getFightingHitBox().getRenderWidth() / 2 - healthBarWidth / 2;
    int centerXPlayer = player->getFightingHitBox().getX() + player->getFightingHitBox().getRenderWidth() / 2 - healthBarWidth / 2;

    enemy->drawHealthBar(centerXEnemy, 64, healthBarWidth, 25, enemy->getHealth(), enemy->getMaxHealth());
    player->drawHealthBar(centerXPlayer, 64, healthBarWidth, 25, player->getHealth(), player->getMaxHealth());

    // render attack buttons
    player->drawAttackList();

    ofSetColor(255, 255, 255);
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
    if(key == OF_KEY_ESC) {
        setNextState(CurrentState::PAUSED);
        setFinished(true);
    }
}

void BattleState::reset() {
    setFinished(false);
    setNextState(CurrentState::NONE);
}