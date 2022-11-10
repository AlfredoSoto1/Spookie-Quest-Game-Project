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
    enemyHasChosenAttack = false;
    isEnemyOnAttack = false;
    hasDied = false;
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

void BattleState::update() {

    //update sprite animation
    player->fightingUpdate();
    enemy->fightingUpdate();

    if(!isAttacking)
        return;
    
    if(player->getHealth() <= 0) {
        setNextState(CurrentState::END);
        setFinished(true);
        return;
    }

    //Player attacks
    Attack& playerAttack = player->getAttack(player->getAttackChoice());
    int currentEnemyHealth = enemy->getHealth();
    playerAttack.provokeAttack(&currentEnemyHealth, 1);
    enemy->setHealth(currentEnemyHealth);

    Boss* boss = dynamic_cast<Boss*>(enemy);
    if(enemy->getHealth() <= 0 && boss == nullptr && !playerAttack.isOnCoolDown()) {
        /*
            end battle if normal enemy dies
        */
        if(!enemy->getDeath()->hasEnded()) {
            enemy->getDeath()->update();
            return;
        }
        boss->getDeath()->reset();  
        setNextState(CurrentState::WIN);
        setFinished(true);
        canInteract = true;
        isAttacking = false;
        enemyHasChosenAttack = false;
        isEnemyOnAttack = false;
        hasDied = false;
        return;
    }else if(boss != nullptr && !playerAttack.isOnCoolDown()) {
        /*
            if enemy is a boss, go to next boss phase
        */
        if(!boss->hasPhasesLeft()) {
            if(!boss->getDeath()->hasEnded()) {
                boss->getDeath()->update();
                return;
            }
            boss->getDeath()->reset();
            setNextState(CurrentState::WIN);
            setFinished(true);
            canInteract = true;
            isAttacking = false;
            enemyHasChosenAttack = false;
            isEnemyOnAttack = false;
            hasDied = false;
            return;
        }
        if(boss->passToNextPhase()) {
            boss->reHeal();
            isEnemyOnAttack = false;
            return;
        }
    }

    if(enemy->getHealth() <= 0)
        return;

    //Enemy Attacks
    if(!enemyHasChosenAttack) {
        enemy->setAttackChoice(rand() % enemy->getNumberOfAttacks());
        enemyHasChosenAttack = true;
    }
    Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());
    if(!playerAttack.isOnCoolDown()) {
        int currentPlayerHealth = player->getHealth();
        enemyAttack.provokeAttack(&currentPlayerHealth, enemy->getBaseDamage());
        player->setHealth(currentPlayerHealth);
        enemyAttack.getAnimation()->update();
        displayAttack = enemyAttack.getAnimation()->getCurrentFrame();
        isEnemyOnAttack = true;
    }

    //reset for next round
    if(!enemyAttack.isOnCoolDown() && !playerAttack.isOnCoolDown()) {
        enemyAttack.reset();
        playerAttack.reset();
        canInteract = true;
        isAttacking = false;
        enemyHasChosenAttack = false;
        isEnemyOnAttack = false;
        hasDied = false;
    }
}

void BattleState::draw() {
    // render stage
    stage.draw(0, 0, ofGetWidth(), ofGetHeight());

    // render combatant sprites
    player->fightingDraw();
    if(enemy->getHealth() <= 0) {
        displayDeath = enemy->getDeath()->getCurrentFrame();
        HitBox& fightingHitbox = enemy->getFightingHitBox();
        displayDeath.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayDeath.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
    } else if(isEnemyOnAttack) {
        HitBox& fightingHitbox = enemy->getFightingHitBox();
        displayAttack.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayAttack.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
    } else {
        enemy->fightingDraw();
    }

    //draw healthBar from both enemy and player
    int healthBarWidth = 256;
    int centerXEnemy = enemy->getFightingHitBox().getX() + enemy->getFightingHitBox().getWidth() / 2 - healthBarWidth / 2;
    int centerXPlayer = player->getFightingHitBox().getX() + player->getFightingHitBox().getWidth() / 2 - healthBarWidth / 2;

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