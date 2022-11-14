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
        default setup
    */
    this->player = player;
    currentButton = 1;
    resultTimer = 0;
    canInteract = true;
    isAttacking = false;
    enemyHasChosenAttack = false;
    isEnemyOnAttack = false;
    isPlayerOnAttack = false;
}

Enemy* BattleState::getEnemy() {
    return enemy;
}

void BattleState::setEnemy(Enemy *enemy) {
    this->enemy = enemy;
}

void BattleState::setStage(Area* area) {
    this->stage = area->getStage();
}

void BattleState::startBattle(Enemy *enemy) {
    this->enemy = enemy;
}

void BattleState::update() {

    //update sprite animation
    player->fightingUpdate();
    enemy->fightingUpdate();

    if(player->getHealth() <= 0) {
        Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());
        enemyAttack.getAnimation()->update();
        displayEnemyAttack = enemyAttack.getAnimation()->getCurrentFrame();
        if(enemyAttack.hasProjectile()) {
            enemyAttack.updateProjectileTraslation();
            enemyAttack.getProjectileAnimation()->update();
            displayEnemyProjectile = enemyAttack.getProjectileAnimation()->getCurrentFrame();
        }
        isEnemyOnAttack = true;

        if(!player->getDeath()->hasEnded()) {
            player->getDeath()->update();
            return;
        }
        player->getDeath()->reset();

        enemyAttack.reset();
        Attack& playerAttack = player->getAttack(player->getAttackChoice());
        playerAttack.reset();
        setNextState(CurrentState::END);
        setFinished(true);
        canInteract = true;
        isAttacking = false;
        enemyHasChosenAttack = false;
        isEnemyOnAttack = false;
        isPlayerOnAttack = false;
        return;
    }
    if(enemy->getHealth() <= 0) {
        Boss* boss = dynamic_cast<Boss*>(enemy);
        if(boss == nullptr) {
            //player strikes last attack animation
            Attack& playerAttack = player->getAttack(player->getAttackChoice());
            playerAttack.getAnimation()->update();
            displayPlayerAttack = playerAttack.getAnimation()->getCurrentFrame();
            isPlayerOnAttack = true;
            //default enemy dies
            if(!enemy->getDeath()->hasEnded()) {
                enemy->getDeath()->update();
                return;
            }
            enemy->getDeath()->reset();
            Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());
            enemyAttack.reset();
            playerAttack.reset();
            setNextState(CurrentState::WIN);
            setFinished(true);
            canInteract = true;
            isAttacking = false;
            enemyHasChosenAttack = false;
            isEnemyOnAttack = false;
            isPlayerOnAttack = false;
            return;
        }else {
            //boss enemy dies
            if(!boss->hasPhasesLeft()) {
                //player strikes last attack animation
                Attack& playerAttack = player->getAttack(player->getAttackChoice());
                playerAttack.getAnimation()->update();
                displayPlayerAttack = playerAttack.getAnimation()->getCurrentFrame();
                isPlayerOnAttack = true;
                if(!boss->getDeath()->hasEnded()) {
                    boss->getDeath()->update();
                    return;
                }
                boss->getDeath()->reset();
                Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());
                enemyAttack.reset();
                playerAttack.reset();
                boss->reset();
                setNextState(CurrentState::WIN);
                setFinished(true);
                canInteract = true;
                isAttacking = false;
                enemyHasChosenAttack = false;
                isEnemyOnAttack = false;
                isPlayerOnAttack = false;
                return;
            }
        }
    }

    Boss* boss = dynamic_cast<Boss*>(enemy);
    if(boss != nullptr) {
        if(boss->passToNextPhase()) {
            boss->reHeal();
            isEnemyOnAttack = false;
            return;
        }
    }

    if(!isAttacking)
        return;

    //Player attacks
    Attack& playerAttack = player->getAttack(player->getAttackChoice());
    int currentEnemyHealth = enemy->getHealth();
    playerAttack.provokeAttack(&currentEnemyHealth, 1);
    enemy->setHealth(currentEnemyHealth);
    if(!isEnemyOnAttack) {
        //player attack animation
        playerAttack.getAnimation()->update();
        displayPlayerAttack = playerAttack.getAnimation()->getCurrentFrame();
        //update enemy hit
        enemy->getHit()->update();
        displayEnemyHit = enemy->getHit()->getCurrentFrame();
        isPlayerOnAttack = true;
    }

    //enemy chooses attack
    if(!enemyHasChosenAttack) {
        enemy->setAttackChoice(rand() % enemy->getNumberOfAttacks());
        enemyHasChosenAttack = true;
    }
    Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());

    //Enemy Attacks
    if(!playerAttack.isOnCoolDown()) {
        int currentPlayerHealth = player->getHealth();
        enemyAttack.provokeAttack(&currentPlayerHealth, enemy->getBaseDamage());
        player->setHealth(currentPlayerHealth);
        //update enemy attack animation
        enemyAttack.getAnimation()->update();
        displayEnemyAttack = enemyAttack.getAnimation()->getCurrentFrame();
        if(enemyAttack.hasProjectile()) {
            enemyAttack.updateProjectileTraslation();
            enemyAttack.getProjectileAnimation()->update();
            displayEnemyProjectile = enemyAttack.getProjectileAnimation()->getCurrentFrame();
        }
        //update player hit
        player->getHit()->update();
        displayPlayerHit = player->getHit()->getCurrentFrame();
        isEnemyOnAttack = true;
        isPlayerOnAttack = false;
    }

    //reset for next round
    if(!enemyAttack.isOnCoolDown() && !playerAttack.isOnCoolDown()) {
        enemyAttack.reset();
        playerAttack.reset();
        canInteract = true;
        isAttacking = false;
        enemyHasChosenAttack = false;
        isEnemyOnAttack = false;
        isPlayerOnAttack = false;
    }
}

void BattleState::draw() {
    // render stage
    stage.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    stage.draw(0, 0, ofGetWidth(), ofGetHeight());

    // render combatant sprites
    if(player->getHealth() <= 0) {
        displayPlayerDeath = player->getDeath()->getCurrentFrame();
        HitBox& fightingHitbox = player->getFightingHitBox();
        displayPlayerDeath.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayPlayerDeath.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
    } else if(isPlayerOnAttack) {
        HitBox& fightingHitbox = player->getFightingHitBox();
        displayPlayerAttack.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayPlayerAttack.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
    } else if(isEnemyOnAttack) {
        HitBox& fightingHitbox = player->getFightingHitBox();
        displayPlayerHit.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayPlayerHit.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
    }else {
        player->fightingDraw();
    }
    if(enemy->getHealth() <= 0) {
        displayEnemyDeath = enemy->getDeath()->getCurrentFrame();
        HitBox& fightingHitbox = enemy->getFightingHitBox();
        displayEnemyDeath.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayEnemyDeath.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
    } else if(isEnemyOnAttack) {
        HitBox& fightingHitbox = enemy->getFightingHitBox();
        displayEnemyAttack.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayEnemyAttack.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());

        //draw enemy projectile if has any    
        Attack& enemyAttack = enemy->getAttack(enemy->getAttackChoice());
        if(enemyAttack.hasProjectile()) {
            displayEnemyProjectile.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
            displayEnemyProjectile.draw(fightingHitbox.getRenderX() - enemyAttack.getProjectileTraslation(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
        }
    } else if(isPlayerOnAttack) {
        HitBox& fightingHitbox = enemy->getFightingHitBox();
        displayEnemyHit.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        displayEnemyHit.draw(fightingHitbox.getRenderX(), fightingHitbox.getRenderY(), fightingHitbox.getRenderWidth(), fightingHitbox.getRenderHeight());
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