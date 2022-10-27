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
    // player->setOX(area->getEntrancePos().x);
    // player->setOY(area->getEntrancePos().y);
    HitBox& playerHitbox = player->getHitBox();
    playerHitbox.setX(area->getEntrancePos().x);
    playerHitbox.setY(area->getEntrancePos().y);
}

void OverworldState::update() {
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
    camera->update();
}

void OverworldState::draw() {
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->inOverworldDraw();

    for (unsigned int i = 0; i < area->getEnemies().size(); i++) {
        Enemy& enemy = *(area->getEnemies().at(i));
        if (!enemy.isDead()) {
            // int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            // int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            HitBox& enemyHitbox = enemy.getHitBox();
            int playerDistanceX = enemyHitbox.getX() - camera->getPlayerX();
            int playerDistanceY = enemyHitbox.getY() - camera->getPlayerY();
            enemy.setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            enemy.setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            enemy.inOverworldDraw();
        }
    }

    if(area->rock == nullptr)
        return;

    HitBox& rockHitbox = area->rock->getHitBox();
    int playerDistanceX = rockHitbox.getX() - camera->getPlayerX();
    int playerDistanceY = rockHitbox.getY() - camera->getPlayerY();
    area->rock->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
    area->rock->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
    area->rock->inOverworldDraw();
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