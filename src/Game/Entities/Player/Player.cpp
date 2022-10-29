#include "Player.h"

Player::Player(int health, int baseDamage) : 
    EntityFighter(HitBox(INIT_X, INIT_Y, 64, 64), HitBox(INIT_BATTLE_X, INIT_BATTLE_Y, 192, 192), health, baseDamage)
{
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    vector<ofImage> fightingFrames;
    ofImage temp;

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

    temp.load("images/entities/player/fightingframes/player-f1.png");
    fightingFrames.push_back(temp);
    temp.load("images/entities/player/fightingframes/player-f2.png");
    fightingFrames.push_back(temp);

    walkDown = new Animation(5, downFrames);
    walkUp = new Animation(5, upFrames);
    walkLeft = new Animation(5, leftFrames);
    walkRight = new Animation(5, rightFrames);
    fighting = new Animation(7, fightingFrames);

}

void Player::inOverworldUpdate() {
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
                if (hitbox.getX() + speed < OXDIMENSION)
                    hitbox.setX(hitbox.getX() + speed);
                else
                    hitbox.setX(OXDIMENSION);
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
                if (hitbox.getY() + speed < OYDIMENSION)
                    hitbox.setY(hitbox.getY() + speed);
                else
                    hitbox.setY(OYDIMENSION);
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
}

void Player::inOverworldDraw() {
    //worldPosition
    float ox = hitbox.getX() - hitbox.getWidth()/2;
    float oy = hitbox.getY() - hitbox.getHeight()/2;

    //screen position
    ox = ofGetWidth() * ox / OXDIMENSION;
    oy = ofGetHeight() * oy / OXDIMENSION;

    overworldSprite.draw(ox, oy, hitbox.getWidth(), hitbox.getHeight());
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
    hitbox.setX(INIT_X);
    hitbox.setY(INIT_Y);
    fightingHitbox.setX(INIT_BATTLE_X);
    fightingHitbox.setY(INIT_BATTLE_Y);
    health = 100;
}

Player::~Player() {
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}