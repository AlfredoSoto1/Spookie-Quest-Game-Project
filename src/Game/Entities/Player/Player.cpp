#include "Player.h"
#include "OverworldCamera.h"

Player::Player(const string& playerName, int health, int baseDamage) : 
    EntityFighter(playerName, HitBox(0, 0, 64, 64), HitBox(64, 64, 192, 192), health, baseDamage)
{

    /*
        load player inventory
    */
    inventory = new Inventory();
    // ofImage item1;
    // item1.load("images/items/sword_1.png");
    // inventory->addItem(Item(item1));
    // item1.load("images/items/sword_2.png");
    // inventory->addItem(Item(item1));
    // item1.load("images/items/sword_3.png");
    // inventory->addItem(Item(item1));
    // item1.load("images/items/potion.png");
    // inventory->addItem(Item(item1));

    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    vector<ofImage> deathFrames;
    vector<ofImage> hitFrames;
    ofImage temp;
    ofImage sprite;

    /*
        Load fight sprites
    */

    for (int i = 1; i < 5; i++) {
        temp.load("images/entities/player/downframes/player-ow-front" + std::to_string(i == 3 ? 1 : i) + ".png");
        downFrames.push_back(temp);
        temp.load("images/entities/player/upframes/player-ow-up" + std::to_string(i == 3 ? 1 : i) + ".png");
        upFrames.push_back(temp);
        temp.load("images/entities/player/leftframes/player-ow-left" + std::to_string(i == 3 ? 1 : i) + ".png");
        leftFrames.push_back(temp);
        temp.load("images/entities/player/rightframes/player-ow-right" + std::to_string(i == 3 ? 1 : i) + ".png");
        rightFrames.push_back(temp);
    }

    vector<ofImage> idleFrames;
    vector<ofImage> attackFrames1;
    vector<ofImage> attackFrames2;
    vector<ofImage> attackFrames3;

    obtainFramesOf(&idleFrames,    4, 137, 86, "images/entities/player/Idle.png");
    obtainFramesOf(&attackFrames1, 5, 137, 86, "images/entities/player/player_attack.png");
    obtainFramesOf(&attackFrames2, 4, 137, 86, "images/entities/player/player_attack2.png");
    obtainFramesOf(&attackFrames3, 4, 137, 86, "images/entities/player/player_attack3.png");
    obtainFramesOf(&deathFrames,   6, 137, 86, "images/entities/player/Death.png");
    obtainFramesOf(&hitFrames,   3, 137, 86, "images/entities/player/Hit.png");

    /*
        Load walking sprites
    */
    walkDown = new Animation(5, downFrames);
    walkUp = new Animation(5, upFrames);
    walkLeft = new Animation(5, leftFrames);
    walkRight = new Animation(5, rightFrames);
    fighting = new Animation(7, idleFrames);

    hit = new Animation(7, hitFrames);

    death = new Animation(10, deathFrames);
    death->setShowOnce(true);

    //set attacks
    Attack attack1 = Attack(new Animation(4, attackFrames1),  8, 50);
    Attack attack2 = Attack(new Animation(4, attackFrames2),  6, 50);
    Attack attack3 = Attack(new Animation(4, attackFrames3),  4, 50);

    ofImage buttonAttackTemp;
    buttonAttackTemp.load("images/ui/buttons/Attack1.png");
    attack1.setAttackLooks(buttonAttackTemp);
    buttonAttackTemp.load("images/ui/buttons/Attack2.png");
    attack2.setAttackLooks(buttonAttackTemp);
    buttonAttackTemp.load("images/ui/buttons/Attack3.png");
    attack3.setAttackLooks(buttonAttackTemp);

    addAttack(attack1);    
    addAttack(attack2);    
    addAttack(attack3);    
}

Player::~Player() {
    delete inventory;

    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;

    delete death;
    delete hit;
    
    vector<Attack>& attacks = getAttacks();
    for(unsigned int i = 0;i < attacks.size(); i++) {
        if(attacks[i].getAnimation() != nullptr)
            delete attacks[i].getAnimation();
    }
}

void Player::obtainFramesOf(vector<ofImage>* frames, int frameCount, int imgWidth, int imgHeight, const string& path) {
    ofImage sprite;
    ofImage temp;
    sprite.load(path);
    for(int i = 0; i < frameCount; i++) {
        temp.cropFrom(sprite, i * imgWidth, 0, imgWidth, imgHeight);
        frames->push_back(temp);
    }
}

Animation* Player::getHit() {
    return hit;
}

Animation* Player::getDeath() {
    return death;
}

Inventory* Player::getInventory() {
    return inventory;
}

void Player::loadCamera(void* camera) {
    this->camera = camera;
}

void Player::drawAttackList() {
    /*
        Draw Button for attacks depending how much the player has
    */
    for(unsigned int i = 0; i < attacks.size(); i++) {
        if(attackChoice == (int)i)
            ofSetColor(255, 255, 255);
        else
            ofSetColor(180, 180, 180);
        int leftX = ofGetWidth() / 2 - (int)(attacks[i].getAttackLooks().getWidth() * attacks.size() / 2);

        attacks[i].getAttackLooks().getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        attacks[i].getAttackLooks().draw(
            leftX + i * attacks[i].getAttackLooks().getWidth(), 
            ofGetHeight() - attacks[i].getAttackLooks().getHeight(),
            attacks[i].getAttackLooks().getWidth(),
            attacks[i].getAttackLooks().getWidth());
    }

    ofSetColor(255, 255, 255);//go back to full brightness
}

void Player::inOverworldUpdate() {
    OverworldCamera* cameraPtr = static_cast<OverworldCamera*>(camera);
    if (!pressedKeys.empty()) {
        switch (pressedKeys[0]) {
            case 'a':
                hitbox.setDirection(Direction::left);

                if (hitbox.getX() - speed > 0)
                    hitbox.setX(hitbox.getX() - speed);
                else
                    hitbox.setX(0);
                walkLeft->update();
                overworldSprite = walkLeft->getCurrentFrame();
                break;
            case 'd':
                hitbox.setDirection(Direction::right);
                if (hitbox.getX() + speed < cameraPtr->getCurrentAreaWidth())
                    hitbox.setX(hitbox.getX() + speed);
                else
                    hitbox.setX(cameraPtr->getCurrentAreaWidth());
                walkRight->update();
                overworldSprite = walkRight->getCurrentFrame();
                break;
            case 'w':
                hitbox.setDirection(Direction::up);
                if (hitbox.getY() - speed > 0)
                    hitbox.setY(hitbox.getY() - speed);
                else
                    hitbox.setY(0);
                walkUp->update();
                overworldSprite = walkUp->getCurrentFrame();
                break;
            case 's':
                hitbox.setDirection(Direction::down);
                if (hitbox.getY() + speed < cameraPtr->getCurrentAreaHeight())
                    hitbox.setY(hitbox.getY() + speed);
                else
                    hitbox.setY(cameraPtr->getCurrentAreaHeight());
                walkDown->update();
                overworldSprite = walkDown->getCurrentFrame();
                break;
        }
    } else {
        switch (hitbox.getDirection()) {
            case Direction::left:
                overworldSprite = walkLeft->getCurrentFrame();
                break;
            case Direction::right:
                overworldSprite = walkRight->getCurrentFrame();
                break;
            case Direction::up:
                overworldSprite = walkUp->getCurrentFrame();
                break;
            case Direction::down:
                overworldSprite = walkDown->getCurrentFrame();
                break;
        }
    }
}

void Player::fightingUpdate() {
    fightingSprite = fighting->getCurrentFrame();
    fighting->update();

    int xpos = ofGetWidth() * (1.0 / 4.0) - fightingHitbox.getWidth() / 2;
    int ypos = ofGetHeight() * (1.0 / 2.0) - fightingHitbox.getHeight() / 2;

    fightingHitbox.setX(xpos);
    fightingHitbox.setY(ypos);
}

void Player::inOverworldDraw(void* camera) {

    OverworldCamera* cameraPtr = static_cast<OverworldCamera*>(camera);

    double xAspectDif = ofGetWidth() / cameraPtr->getLenzWidth();
    double yAspectDif = ofGetHeight() / cameraPtr->getLenzHeight();

    int aspectWidth = hitbox.getRenderWidth() * xAspectDif;
    int aspectHeight = hitbox.getRenderHeight() * yAspectDif;
    
    float xRender = ofGetWidth() / 2 - aspectWidth / 2;
    float yRender = ofGetHeight() / 2 - aspectHeight / 2;

    if(hitbox.getX() < cameraPtr->getLenzWidth() / 2) {
        // xRender = hitbox.getRenderX() - aspectWidth / 2;
        float leftCorner = cameraPtr->getLenzWidth() / 2;
        float leftCornerDif = leftCorner - hitbox.getRenderX();
        float ratio = leftCornerDif / (cameraPtr->getLenzWidth() / 2);
        xRender = ofGetWidth() / 2 - aspectWidth/2 - ratio * ofGetWidth() / 2;
    } else if(hitbox.getX() > cameraPtr->getCurrentAreaWidth() - cameraPtr->getLenzWidth() / 2) {
        // xRender = hitbox.getRenderX() - (OXDIMENSION - cameraPtr->getLenzWidth() / 2) + ofGetWidth() / 2 - aspectWidth/2;
        float rightCorner = cameraPtr->getCurrentAreaWidth() - cameraPtr->getLenzWidth() / 2;
        float rightCornerDif = hitbox.getRenderX() - rightCorner;
        float ratio = rightCornerDif / (cameraPtr->getLenzWidth() / 2);
        xRender = ofGetWidth() / 2 - aspectWidth/2 + ratio * ofGetWidth() / 2;
    }

    if(hitbox.getY() < cameraPtr->getLenzHeight() / 2) {
        // yRender = hitbox.getRenderY() - aspectHeight/2;
        float topCorner = cameraPtr->getLenzHeight() / 2;
        float topCornerDif = topCorner - hitbox.getRenderY();
        float ratio = topCornerDif / (cameraPtr->getLenzHeight() / 2);
        yRender = ofGetHeight() / 2 - aspectHeight/2 - ratio * ofGetHeight() / 2;
    } else if(hitbox.getY() > cameraPtr->getCurrentAreaHeight() - cameraPtr->getLenzHeight() / 2) {
        // yRender = hitbox.getRenderY() - (OYDIMENSION - cameraPtr->getLenzHeight() / 2) + ofGetHeight() / 2 - aspectHeight/2;
        float downCorner = cameraPtr->getCurrentAreaHeight()- cameraPtr->getLenzHeight() / 2;
        float downCornerDif = hitbox.getRenderY() - downCorner;
        float ratio = downCornerDif / (cameraPtr->getLenzHeight() / 2);
        yRender = ofGetHeight() / 2 - aspectHeight/2 + ratio * ofGetHeight() / 2;
    }

    overworldSprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    overworldSprite.draw(xRender, yRender, aspectWidth, aspectHeight);
}

void Player::keyPressed(int key) {
    if (key == 'w' || key == 'a' || key == 's' || key == 'd')
        if (find(pressedKeys.begin(), pressedKeys.end(), key) == pressedKeys.end())
            pressedKeys.push_back(key);
}

void Player::keyReleased(int key) {
    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        vector<char>::iterator pos = find(pressedKeys.begin(), pressedKeys.end(), key);
        if (pos != pressedKeys.end())
            pressedKeys.erase(pos);
    }
}

void Player::reset() {
    hitbox.setX(0);
    hitbox.setY(0);
    fightingHitbox.setX(64);
    fightingHitbox.setY(64);
    health = maxHealth;
}