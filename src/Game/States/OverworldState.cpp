#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area) {
    this->setCurrentState(CurrentState::OVERWORLD);
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
}

Player* OverworldState::getPlayer() { 
    return player; 
}

Enemy* OverworldState::getEnemyToBattle() {
    return enemyToBattle;
}

void OverworldState::setEnemy(Enemy *enemyToBattle) {
    this->enemyToBattle = enemyToBattle;
}

Area* OverworldState::getArea() {
    return area;
}

void OverworldState::loadArea(Area* area) {
    this->area = area;
    overworldImage = area->getImage();
    overworldEffectImage = area->getAmbianceImage();
    overWorldAreaImageBoundry = area->getAreaImageBoundry();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    HitBox& playerHitbox = player->getHitBox();

    //set Player position
    playerHitbox.setX(area->getEntrancePos().x);
    playerHitbox.setY(area->getEntrancePos().y);
}

void OverworldState::update() {
    camera->update();

    player->inOverworldUpdate();

    // if(player->getHealth() <= 0) {
    //     setFinished(true);
    //     setNextState(CurrentState::END);
    //     return;
    // }

    //player Hitbox
    HitBox& playerHitbox = player->getHitBox();

    ofColor inColorBoundry = playerHitbox.collides(ofColor::white, overWorldAreaImageBoundry);

    // if(inColorBoundry == ofColor::red){
    //     player->setHealth(player->getHealth() - 2);
    // }    

    for(Entity* entity : area->getEntities()) {
        //Update enemies

        Enemy* enemy = dynamic_cast<Enemy*>(entity);
        if(enemy != nullptr) {
            Boss* boss = dynamic_cast<Boss*>(enemy);
            if(boss != nullptr)
                if(!area->inBossFight())
                    continue;

            if (!enemy->isDead()) {
                enemy->inOverworldUpdate();
                if (playerHitbox.collides(enemy->getHitBox())) {
                    setEnemy(enemy);
                    setNextState(CurrentState::BATTLE);
                    setFinished(true);
                    break;
                }
            }
            continue;
        }
        //update other entities here
        //change this to inmovable/structure entity
        Structure* rock = dynamic_cast<Structure*>(entity);
        if(rock != nullptr) { 
            rock->inOverworldUpdate();
            HitBox& rockHitbox = rock->getHitBox();
            playerHitbox.collides(rockHitbox);
            continue;
        }
    }
}






void OverworldState::draw() {
    /*
        Draw Arena
    */
    overworldImage.drawSubsection(
        0, 0,                                               //position in screen
        ofGetWidth(), ofGetHeight(),                        //final image scale on screen
        camera->getLeftCornerX(), camera->getTopCornerY(),  //position in image
        camera->getLenzWidth(), camera->getLenzHeight());   //scale in image

    // //debug regions
    // overWorldAreaImageBoundry.drawSubsection(
    //     0, 0,                                               //position in screen
    //     ofGetWidth(), ofGetHeight(),                        //final image scale on screen
    //     camera->getLeftCornerX(), camera->getTopCornerY(),  //position in image
    //     camera->getLenzWidth(), camera->getLenzHeight());   //scale in image

    /*
        Draw Player
    */
    player->inOverworldDraw(camera);

    
    /*
        Draw Entities
    */

    for(Entity* entity : area->getEntities()) {
        //draw enemies
        Enemy* enemy = dynamic_cast<Enemy*>(entity);
        if(enemy != nullptr) {
            Boss* boss = dynamic_cast<Boss*>(enemy);
            if(boss != nullptr)
                if(!area->inBossFight())
                    continue;
            if (!enemy->isDead()) {
                enemy->inOverworldDraw(camera);
            }
            continue;
        }
        Structure* structure = dynamic_cast<Structure*>(entity);
        if(structure != nullptr) { 
            structure->inOverworldDraw(camera);
            continue;
        }

    }

    // Draw HUD
    ofSetColor(ofColor::black);
    ofDrawRectangle(10,30,440,140);
    ofSetColor(ofColor::gray);
    ofDrawRectangle(30,45,400,110);
    ofSetColor(ofColor::white);
    ofDrawBitmapString("PLAYER POSITION " + ofToString(player->getHitBox().getX()) + ", " + ofToString(player->getHitBox().getY()), 50, 80);
    ofDrawBitmapString("ENEMIES ALIVE: " + ofToString(area->getRemainingEnemies()), 50, 100);
     ofDrawBitmapString("HEALTH: ", 50, 126);
    player->drawHealthBar(120, 110, 256, 25, player->getHealth(), player->getMaxHealth());
    ofDrawBitmapString(ofToString(floor(player->getHealth() * .10)* 2) + "%", 385, 126);

    //draw Effect
    // overworldEffectImage.draw(0,0, ofGetWidth(), ofGetHeight());
}



void OverworldState::keyPressed(int key) {
    player->keyPressed(key);
    if(key == 'b')
        area->setInBossFight(true);
    else if(key == OF_KEY_ESC) {
        setNextState(CurrentState::PAUSED);
        setFinished(true);
    }
}

void OverworldState::keyReleased(int key) {
    player->keyReleased(key);
}

void OverworldState::reset() {
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState(CurrentState::NONE);
}