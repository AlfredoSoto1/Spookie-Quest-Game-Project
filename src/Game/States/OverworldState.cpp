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
    playerHitbox.setX(OXDIMENSION / 2);
    playerHitbox.setY(OYDIMENSION / 2);
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
            if (!enemy->isDead()) {
                enemy->inOverworldUpdate();
                if (playerHitbox.collides(enemy->getHitBox())) {
                    setEnemy(enemy);
                    setNextState("Battle");
                    setFinished(true);
                    break;
                }
            }
        }
        //update other entities here
        //change this to inmovable/structure entity
        Rock* rock = dynamic_cast<Rock*>(entity);
        if(rock != nullptr) { 
            rock->inOverworldUpdate();
            HitBox& rockHitbox = rock->getHitBox();
            playerHitbox.collides(rockHitbox);
        }

        //do else after here
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

    /*
        Draw Entities
    */

    for(Entity* entity : area->getEntities()) {
        //Update enemies
        Enemy* enemy = dynamic_cast<Enemy*>(entity);
        if(enemy != nullptr) {
            if (!enemy->isDead()) {
                enemy->inOverworldDraw(camera);
            }
        }
        Rock* rock = dynamic_cast<Rock*>(entity);
        if(rock != nullptr) { 
            rock->inOverworldDraw(camera);
        }
    }
}

void OverworldState::keyPressed(int key) {
    player->keyPressed(key);
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
    setNextState("");
}