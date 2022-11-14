#include "Friend.h"
#include "OverworldCamera.h"

Friend::Friend(const string& name, FriendE friendType, int ox, int oy)
    : Entity(name, HitBox(ox, oy, 100, 100), 100)
{
    /*
        Load Friend interactions
    */
    ofImage tempText;
    tempText.load("images/entities/friend/text.png");

    textNineSlice[0].cropFrom(tempText, 0 , 0, 4, 4);
    textNineSlice[1].cropFrom(tempText, 5 , 0, 6, 4);
    textNineSlice[2].cropFrom(tempText, 12, 0, 4, 4);

    textNineSlice[3].cropFrom(tempText, 0 , 5, 4, 6);
    textNineSlice[4].cropFrom(tempText, 5 , 5, 6, 6);
    textNineSlice[5].cropFrom(tempText, 12, 5, 4, 6);

    textNineSlice[6].cropFrom(tempText, 0 , 12, 4, 4);
    textNineSlice[7].cropFrom(tempText, 5 , 12, 6, 4);
    textNineSlice[8].cropFrom(tempText, 12, 12, 4, 4);
    /*
        load Friend propeties
    */
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
    initialSpeed = speed;
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
    isInteracting = true;
}

void Friend::inOverworldUpdate() {

    if(isInteracting) {
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
        return;
    }
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

void Friend::drawInteraction(void* camera) {
    if(!isInteracting)
        return;

    int speechBlockWidth = 400;
    int speechBlockHeight = 100;
    drawSpeech(ofGetWidth()/2 - speechBlockWidth / 2, ofGetHeight() / 2 + 100, speechBlockWidth, speechBlockHeight, 10);

    ofDrawBitmapString("Here, take this elixir. It can heal you back", ofGetWidth()/2 - speechBlockWidth / 2 + 20, ofGetHeight() / 2 + 120);
    ofDrawBitmapString("from all the damages you took", ofGetWidth()/2 - speechBlockWidth / 2 + 20, ofGetHeight() / 2 + 140);
    ofDrawBitmapString("Press Enter to collect item, once", ofGetWidth()/2 - speechBlockWidth / 2 + 20, ofGetHeight() / 2 + 160);

    isInteracting = false;
}

void Friend::drawSpeech(int x, int y, int width, int height, int borderSize) {
    textNineSlice[0].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[1].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[2].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[3].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[4].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[5].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[6].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[8].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    textNineSlice[7].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    textNineSlice[0].draw(x                                    , y             , borderSize          , borderSize);
    textNineSlice[1].draw(x + borderSize                       , y             , width - borderSize/2, borderSize);
    textNineSlice[2].draw(x + borderSize + width - borderSize/2, y             , borderSize          , borderSize);

    textNineSlice[3].draw(x                                    , y + borderSize, borderSize          , height - borderSize/2);
    textNineSlice[4].draw(x + borderSize                       , y + borderSize, width - borderSize/2, height - borderSize/2);
    textNineSlice[5].draw(x + borderSize + width - borderSize/2, y + borderSize, borderSize          , height - borderSize/2);

    textNineSlice[6].draw(x                                    , y + borderSize + height - borderSize/2, borderSize          , borderSize);
    textNineSlice[7].draw(x + borderSize                       , y + borderSize + height - borderSize/2, width - borderSize/2, borderSize);
    textNineSlice[8].draw(x + borderSize + width - borderSize/2, y + borderSize + height - borderSize/2, borderSize          , borderSize);
}