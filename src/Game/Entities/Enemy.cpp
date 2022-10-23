#include "Enemy.h"

Enemy::Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy) : Entity(ox, oy, 50, 64, 420, 220, 97, 125, health, baseDamage) {
    this->id = id;
    this->entityName = entityName;
    moveTimer = 0;
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

    // if(ofRandom(1.0f) > 0.5)
        angleOfMovement = 180.0;
    // else
    //     angleOfMovement = 0.0;

    movementDirection = glm::vec2(1.0, 0.0);
}

void Enemy::inOverworldUpdate() {
    if (moveTimer == 0) {
        walking = true;

        //change direction
        if(angleOfMovement == 180.0)
            angleOfMovement = 60.0;
        else if(angleOfMovement == 60.0)
            angleOfMovement = -60.0;
        else if(angleOfMovement == -60.0)
            angleOfMovement = 180.0;
        // else if(angleOfMovement == 0.0)
        //     angleOfMovement = 140.0;
        // else if(angleOfMovement == 140.0)
        //     angleOfMovement = -140.0;
        // else if(angleOfMovement == -140.0)
        //     angleOfMovement = 0.0;

        movementDirection.x = glm::cos(angleOfMovement * PI / 180.0);
        movementDirection.y = glm::sin(angleOfMovement * PI / 180.0);
    }
    if (moveTimer == movingTime) {
        walking = false;
    }
    moveTimer++;
    if (moveTimer == movingTime + standingStillTime) moveTimer = 0;

    if (walking) {

         this->ox += movementDirection.x * speed;
         this->oy += movementDirection.y * speed;

        if(movementDirection.x < 0) {
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
        } else if(movementDirection.x > 0) {
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
        } else if(movementDirection.y < 0) {
            walkDown->update();
            overworldSprite = walkDown->getCurrentFrame();
        } else if(movementDirection.y > 0) {
            walkUp->update();
            overworldSprite = walkUp->getCurrentFrame();
        }
    } else {
        if(movementDirection.x < 0)
            overworldSprite = walkLeft->getCurrentFrame();
        else if(movementDirection.x > 0)
            overworldSprite = walkRight->getCurrentFrame();
        else if(movementDirection.y < 0)
            overworldSprite = walkDown->getCurrentFrame();
        else if(movementDirection.y > 0)
            overworldSprite = walkUp->getCurrentFrame();
    }
}

void Enemy::inOverworldDraw() {
    // uncomment these if you want the coordinates of the enemies in the current area
    // ofDrawBitmapString("rX:" + to_string(renderX), 100 + 125 * ((stoi(id) % 10) - 1), 100);
    // ofDrawBitmapString("rY:" + to_string(renderY), 100 + 125 * ((stoi(id) % 10) - 1), 120);
    // ofDrawBitmapString("ow:" + to_string(ox), 100 + 125 * ((stoi(id) % 10) - 1), 140);
    // ofDrawBitmapString("oy:" + to_string(oy), 100 + 125 * ((stoi(id) % 10) - 1), 160);
    overworldSprite.draw(renderX, renderY, ow, oh);
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