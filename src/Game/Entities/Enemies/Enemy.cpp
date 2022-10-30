#include "Enemy.h"
#include "OverworldCamera.h"

Enemy::Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy) : 
    // EntityFighter(ox, oy, 50, 64, 420, 220, 97, 125, health, baseDamage)
    EntityFighter(HitBox(ox, oy, 50, 64), HitBox(420, 220, 97, 125), health, baseDamage)
{
    this->id = id;
    this->entityName = entityName;
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    ofImage sprite;
    ofImage temp;

    sprite.load("images/entities/enemy/sprite.png");

    int w = 48, h = 48;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp.cropFrom(sprite, 6 + w * i, 192 + h * j, w - 12, h);
            if (j == 0)
                downFrames.push_back(temp);
            else if (j == 1)
                leftFrames.push_back(temp);
            else if (j == 2)
                rightFrames.push_back(temp);
            else
                upFrames.push_back(temp);
        }   
    }
    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);
    fighting = new Animation(7, leftFrames);

    speed = 8;
    movingTime = 15;
    standingStillTime = 40;
    timeDirectionCounter = glm::vec2(0.0, 0.0);
    movementDirection = glm::vec2(0.0, 0.0);
    hitbox.setDirection(Direction::up);
}

void Enemy::inOverworldUpdate() {

    if(linePath == 0) {
        movementDirection.x = -2.0;
        movementDirection.y =  0.0;
    } else if(linePath == 1) {
        movementDirection.x =  1.0; 
        movementDirection.y =  1.0; 
    }else if(linePath == 2) {
        movementDirection.x =  1.0;
        movementDirection.y = -1.0;
    }

    bool xFinished = false;
    if(timeDirectionCounter.x < movingTime && walking) {
        // this->ox += movementDirection.x * speed;
        hitbox.setX(hitbox.getX() + movementDirection.x * speed);
        timeDirectionCounter.x++;
    }else {
        xFinished = true;
    }

    bool yFinished = false;
    if(timeDirectionCounter.y < movingTime && walking) {
        // this->oy += movementDirection.y * speed;
        hitbox.setY(hitbox.getY() + movementDirection.y * speed);
        timeDirectionCounter.y++;
    } else {
        yFinished = true;
    }

    if(xFinished && yFinished) {
        timeDirectionCounter.x = 0;
        timeDirectionCounter.y = 0;
        walking = false;
        standingStillCounter++;
    }

    if(standingStillCounter > standingStillTime) {
        standingStillCounter = 0;
        walking = true;
        linePath++;
        if(linePath > 2)
            linePath = 0;
    }

    if(walking) {
        if(movementDirection.x < 0) {
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            hitbox.setDirection(Direction::left);
        } else if(movementDirection.x > 0) {
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            hitbox.setDirection(Direction::right);
        } else if(movementDirection.y > 0) {
            walkDown->update();
            overworldSprite = walkDown->getCurrentFrame();
            hitbox.setDirection(Direction::down);
        } else if(movementDirection.y < 0) {
            walkUp->update();
            overworldSprite = walkUp->getCurrentFrame();
            hitbox.setDirection(Direction::up);
        }
    }else {
        if(movementDirection.x < 0) {
            overworldSprite = walkLeft->getCurrentFrame();
        } else if(movementDirection.x > 0) {
            overworldSprite = walkRight->getCurrentFrame();
        } else if(movementDirection.y > 0) {
            overworldSprite = walkDown->getCurrentFrame();
        } else if(movementDirection.y < 0) {
            overworldSprite = walkUp->getCurrentFrame();
        }      
    }
}

void Enemy::inOverworldDraw(void* camera) {
    OverworldCamera* cameraPtr = static_cast<OverworldCamera*>(camera);

    lastXCam = cameraPtr->getLastMovingDirX() == 0 ? cameraPtr->getCameraX() : lastXCam;
    lastYCam = cameraPtr->getLastMovingDirY() == 0 ? cameraPtr->getCameraY() : lastYCam;

    int playerDistanceX = hitbox.getX() - lastXCam;
    int playerDistanceY = hitbox.getY() - lastYCam;

    renderX = ofGetWidth()  / 2 + playerDistanceX;
    renderY = ofGetHeight() / 2 + playerDistanceY;

    overworldSprite.draw(renderX, renderY, hitbox.getWidth(), hitbox.getHeight());
}

void Enemy::fightingUpdate() {
    fightingSprite = fighting->getCurrentFrame();
    fighting->update();
}

void Enemy::reset() {
}

Enemy::~Enemy() {
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
    delete fighting;
}