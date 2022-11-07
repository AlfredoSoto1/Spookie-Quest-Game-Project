#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area) {
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

    //player Hitbox
    HitBox& playerHitbox = player->getHitBox();
    

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
            else if(enemy->isDead()){
                std::vector<Enemy*>::iterator it = std::find(enemyDead.begin(), enemyDead.end(), enemy);
                if(it == enemyDead.end()){
                    enemyDead.push_back(enemy);
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

    /*
        Draw Player
    */
    player->inOverworldDraw(camera);

    ofDrawBitmapString("player position " + ofToString(player->getHitBox().getX()) + ", " + ofToString(player->getHitBox().getY()), 50, 100);
    ofDrawBitmapString("player health: " + ofToString(player->getHealth()), 50, 50);
    ofDrawBitmapString("enemies dead: " + ofToString(enemyDead.size()), 50, 200);
    

    

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
}

void OverworldState::keyPressed(int key) {
    player->keyPressed(key);
    if(key == 'b')
        area->setInBossFight(true);
    else if(key == 'h'){
        player->setHealth(100);
        
    }
    else if(key == 'r'){
        for(int i = 0; i < enemyDead.size(); i++){
            enemyDead[i]->revive();
            enemyDead.erase(enemyDead.begin() + i);
        }
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