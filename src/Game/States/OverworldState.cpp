#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area) {
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
}

void OverworldState::loadArea(Area *area) {
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    HitBox& playerHitbox = player->getHitBox();
    // playerHitbox.setX(area->getEntrancePos().x);
    // playerHitbox.setY(area->getEntrancePos().y);

    playerHitbox.setX(OXDIMENSION / 2);
    playerHitbox.setY(OYDIMENSION / 2);
}

void OverworldState::update() {
    camera->update();

    player->inOverworldUpdate();

    for (unsigned int i = 0; i < area->getEnemies().size(); i++) {
        Enemy& enemy = *(area->getEnemies().at(i));
        if (!enemy.isDead()) {
            enemy.inOverworldUpdate();
            HitBox& playerHitbox = player->getHitBox();
            if (playerHitbox.collides(enemy.getHitBox())) {
                setEnemy(area->getEnemies().at(i));
                setNextState("Battle");
                setFinished(true);
                break;
            }
        }
    }
    
    area->rock->inOverworldUpdate();

    HitBox& playerHitbox = player->getHitBox();
    HitBox& rockHitbox = area->rock->getHitBox();
    
    playerHitbox.collides(rockHitbox);
}

void OverworldState::draw() {
    // overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());

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
        Draw Enemies
    */
    for (unsigned int i = 0; i < area->getEnemies().size(); i++) {
        Enemy& enemy = *(area->getEnemies().at(i));
        if (!enemy.isDead()) {
            enemy.inOverworldDraw(camera);
        }
    }

    /*
        Draw Entities
    */
    if(area->rock == nullptr)
        return;
    area->rock->inOverworldDraw(camera);

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