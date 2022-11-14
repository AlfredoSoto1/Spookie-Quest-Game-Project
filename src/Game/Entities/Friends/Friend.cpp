#include "Friend.h"
#include "OverworldCamera.h"

Friend::Friend(const string& name, FriendE friendType, int ox, int oy)
    : Entity(name, HitBox(ox, oy, 100, 100), 100)
{
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    vector<ofImage> idleLeftFrames;
    vector<ofImage> idleRightFrames;

    if(friendType == FriendE::WIZZARD) {
        obtainFramesOf(&leftFrames      , 8, 231, 190, "images/entities/friend/wizzard/Run_left.png");
        obtainFramesOf(&rightFrames     , 8, 231, 190, "images/entities/friend/wizzard/Run_right.png");
        obtainFramesOf(&idleLeftFrames  , 6, 231, 190, "images/entities/friend/wizzard/Idle_left.png");
        obtainFramesOf(&idleRightFrames , 6, 231, 190, "images/entities/friend/wizzard/Idle_right.png");
    }

    idleLeft  = new Animation(5, idleLeftFrames);
    idleRight = new Animation(5, idleRightFrames);
    walkLeft  = new Animation(5, leftFrames);
    walkRight = new Animation(5, rightFrames);

    speed = 5;
    movingTime = 15;
    standingStillTime = 50;
    timeDirectionCounter = glm::vec2(0.0, 0.0);
    movementDirection = glm::vec2(0.0, 0.0);
    hitbox.setDirection(Direction::up);
}

Friend::~Friend() {
    delete idleLeft;
    delete idleRight;
    delete walkLeft;
    delete walkRight;
}

void Friend::obtainFramesOf(vector<ofImage>* frames, int frameCount, int imgWidth, int imgHeight, const string& path) {
    ofImage sprite;
    ofImage temp;
    sprite.load(path);
    for(int i = 0; i < frameCount; i++) {
        temp.cropFrom(sprite, i * imgWidth, 0, imgWidth, imgHeight);
        frames->push_back(temp);
    }
}

FriendE Friend::getType() {
    return friendType;
}

void Friend::interact() {
    //friend interaction here
}

void Friend::inOverworldUpdate() {
    //update here
    if(linePath == 0) {
        movementDirection.x = -2.0;
        movementDirection.y =  0.0;
    } else if(linePath == 1) {
        movementDirection.x =  1.0; 
        movementDirection.y =  1.0; 
    } else if(linePath == 2) {
        movementDirection.x =  1.0;
        movementDirection.y = -1.0;
    }

    bool xFinished = false;
    if(timeDirectionCounter.x < movingTime && walking) {
        hitbox.setX(hitbox.getX() + movementDirection.x * speed);
        timeDirectionCounter.x++;
    }else {
        xFinished = true;
    }

    bool yFinished = false;
    if(timeDirectionCounter.y < movingTime && walking) {
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
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            hitbox.setDirection(Direction::down);
        } else if(movementDirection.y < 0) {
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            hitbox.setDirection(Direction::up);
        }
    }else {
        if(movementDirection.x < 0) {
            idleLeft->update();
            overworldSprite = idleLeft->getCurrentFrame();
        } else if(movementDirection.x > 0) {
            idleRight->update();
            overworldSprite = idleRight->getCurrentFrame();
        } else if(movementDirection.y > 0) {
            idleRight->update();
            overworldSprite = idleRight->getCurrentFrame();
        } else if(movementDirection.y < 0) {
            idleRight->update();
            overworldSprite = idleRight->getCurrentFrame();
        }      
    }
}

void Friend::inOverworldDraw(void* camera) {
    OverworldCamera* cameraPtr = static_cast<OverworldCamera*>(camera);

    double xAspectDif = ofGetWidth() / cameraPtr->getLenzWidth();
    double yAspectDif = ofGetHeight() / cameraPtr->getLenzHeight();

    int playerDistanceX = (hitbox.getRenderX() - cameraPtr->getCameraX()) * xAspectDif;
    int playerDistanceY = (hitbox.getRenderY() - cameraPtr->getCameraY()) * yAspectDif;

    renderX = ofGetWidth()  / 2 + playerDistanceX;
    renderY = ofGetHeight() / 2 + playerDistanceY;

    overworldSprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    overworldSprite.draw(renderX, renderY, hitbox.getRenderWidth() * xAspectDif, hitbox.getRenderHeight() * yAspectDif);
}