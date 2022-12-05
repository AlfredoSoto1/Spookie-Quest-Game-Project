#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area) {
    this->setCurrentState(CurrentState::OVERWORLD);
    this->player = player;
    camera = new OverworldCamera(player, area);
    loadArea(area);
    this->friendInteract = false;
    this->debugMapCollider = false;
    this->collectItem = false;
    this->isCollidingFriend = false;
    this->hasOneItem = false;

    vector<ofImage> ambianceFrames;
    ofImage ambianceImage;
    ambianceImage.load("images/areas/darkness_1.png");
    ambianceFrames.push_back(ambianceImage);
    ambianceImage.load("images/areas/darkness_2.png");
    ambianceFrames.push_back(ambianceImage);
    ambianceImage.load("images/areas/darkness_3.png");
    ambianceFrames.push_back(ambianceImage);
    darknessAnimation = new Animation(10, ambianceFrames);

    ofImage itemImage;
    itemImage.load("images/items/potion.png");
    
    item1 = new Item(ItemE::ELIXIR, itemImage);
}

OverworldState::~OverworldState() {
    delete camera;
    delete darknessAnimation;
    delete item1;
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
    overWorldAreaCollider = area->getAreaImageBoundry();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    HitBox& playerHitbox = player->getHitBox();

    //set Player position
    playerHitbox.setX(area->getEntrancePos().x);
    playerHitbox.setY(area->getEntrancePos().y);
}

void OverworldState::update() {

    isCollidingFriend = false;

    darknessAnimation->update();

    if(!friendInteract) {
        camera->update();
        player->inOverworldUpdate();
    }else if(collectItem) {
        player->getInventory()->addItem(*item1);
        collectItem = false;
    }

    if(player->getHealth() <= 0) {
        setFinished(true);
        setNextState(CurrentState::END);
        return;
    }

    //player Hitbox
    HitBox& playerHitbox = player->getHitBox();

    glm::vec4 inColorBoundry = playerHitbox.collides(ofColor::white, overWorldAreaCollider);

    //check if red is dominant
    if(inColorBoundry.r > inColorBoundry.g && inColorBoundry.r > inColorBoundry.b) {
        player->setHealth(player->getHealth() - 4);//"is in lava"
    }

    //check if blue is dominant
    if(inColorBoundry.b > inColorBoundry.g && inColorBoundry.b > inColorBoundry.r) {
        player->setHealth(player->getHealth() - 1);//"is in water"
    }

    //check if black is dominant
    if(inColorBoundry.g > inColorBoundry.r && inColorBoundry.g > inColorBoundry.b) {
        player->setHealth(0);//"fell to void"
    }

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
        
        Structure* structure = dynamic_cast<Structure*>(entity);
        if(structure != nullptr) { 
            structure->inOverworldUpdate();
            HitBox& structureHitBox = structure->getHitBox();
            playerHitbox.collides(structureHitBox);
            continue;
        }

        Friend* npc = dynamic_cast<Friend*>(entity);
        if(npc != nullptr) {
            HitBox& npcHitBox = npc->getHitBox();
            isCollidingFriend = playerHitbox.collides(npcHitBox);
            if(friendInteract && isCollidingFriend) {
                npc->interact();
            }
            npc->inOverworldUpdate();
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

    if(debugMapCollider) {
        //debug regions
        overWorldAreaCollider.drawSubsection(
            0, 0,                                               //position in screen
            ofGetWidth(), ofGetHeight(),                        //final image scale on screen
            camera->getLeftCornerX(), camera->getTopCornerY(),  //position in image
            camera->getLenzWidth(), camera->getLenzHeight());   //scale in image
    }

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

        Friend* npc = dynamic_cast<Friend*>(entity);
        if(npc != nullptr) {
            npc->inOverworldDraw(camera);
            npc->drawInteraction(camera);
            continue;
        }
    }

    //draw Effect on overWorld
    if(area->getType() == AreaE::CAVE) {
        darknessAnimation->getCurrentFrame().draw(0,0, ofGetWidth(), ofGetHeight());
    }

    // Draw HUD
    if(hud == true){
        ofSetColor(ofColor::black);
        ofDrawRectangle(10,30,440,250);
        ofSetColor(ofColor::gray);
        ofDrawRectangle(30,45,400,220);
        ofSetColor(ofColor::white);
        ofDrawBitmapString("AREA: " + ofToString(area->getName()), 50, 80);
        ofDrawBitmapString("ENEMIES ALIVE: " + ofToString(area->getRemainingEnemies()), 50, 100);
        ofDrawBitmapString("HEALTH: ", 50, 126);
        player->drawHealthBar(120, 110, 256, 25, player->getHealth(), player->getMaxHealth());
        ofDrawBitmapString(ofToString((int)(((float)player->getHealth() / player->getMaxHealth()) * 100)) + "%", 385, 126);
        ofDrawBitmapString("PLAYER POSITION " + ofToString(player->getHitBox().getX()) + ", " + ofToString(player->getHitBox().getY()), 50, 155);
        ofDrawBitmapString("DEAD ENEMIES:  " + ofToString(area->getDeadEnemies()), 50, 175);
    }
    else{
        ofSetColor(ofColor::black);
        ofDrawRectangle(10,30,440,140);
        ofSetColor(ofColor::gray);
        ofDrawRectangle(30,45,400,110);
        ofSetColor(ofColor::white);
        ofDrawBitmapString("AREA: " + ofToString(area->getName()), 50, 80);
        ofDrawBitmapString("ENEMIES ALIVE: " + ofToString(area->getRemainingEnemies()), 50, 100);
        ofDrawBitmapString("HEALTH: ", 50, 126);
        player->drawHealthBar(120, 110, 256, 25, player->getHealth(), player->getMaxHealth());
        ofDrawBitmapString(ofToString((int)(((float)player->getHealth() / player->getMaxHealth()) * 100)) + "%", 385, 126);
    }

    player->getInventory()->draw();    
}

void OverworldState::keyPressed(int key) {
    player->keyPressed(key);
    if(key == 'b') {
        area->setInBossFight(true);
    }
    if(key == OF_KEY_ESC) {
        setNextState(CurrentState::PAUSED);
        setFinished(true);
    }
    if(key == 't') {
        debugMapCollider = !debugMapCollider;
    }
    if(key == 'e') {
        if(isCollidingFriend) {
            friendInteract = !friendInteract;
        }
    }
    if(key == 'k') {
        hud = !hud;
    }
    if(key == 'h'){
        player->setHealth(player->getMaxHealth());
    }
    if(key == 'r'){
        for(Entity* entity : area->getEntities()){
            Enemy* enemy = dynamic_cast<Enemy*>(entity);
            if(enemy != nullptr) {
                if (enemy->isDead())
                    enemy->revive();
                continue;
            }
        }
    }
    if(key == OF_KEY_DOWN) {
        player->getInventory()->nextSlot();
    }
    if(key == OF_KEY_UP) {
        player->getInventory()->prevSlot();
    }
    if(key == 'u') {
        if(player->getInventory()->hasItemSlot(ItemE::ELIXIR)) {
            player->getInventory()->removeItem(player->getInventory()->getCurrentSlot());
            player->setHealth(player->getMaxHealth());
            hasOneItem = false;
        }
    }
    if(key == ' ') {
        if(!hasOneItem) {
            collectItem = !collectItem;
        }
        hasOneItem = true;
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
    
    player->keyReleased('e');
    player->keyReleased(' ');
    player->keyReleased('r');
    player->keyReleased('h');
    player->keyReleased('t');
    player->keyReleased('k');
    setFinished(false);
    setNextState(CurrentState::NONE);

    // player->setHealth(player->getMaxHealth());
}