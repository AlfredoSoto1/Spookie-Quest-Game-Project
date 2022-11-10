#include "Player.h"
#include "OverworldCamera.h"

Player::Player(const string& playerName, int health, int baseDamage) : 
    EntityFighter(playerName, HitBox(0, 0, 64, 64), HitBox(64, 64, 192, 192), health, baseDamage)
{
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    vector<ofImage> fightingFrames;
    ofImage temp;

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

    temp.load("images/entities/player/fightingframes/player-f1.png");
    fightingFrames.push_back(temp);
    temp.load("images/entities/player/fightingframes/player-f2.png");
    fightingFrames.push_back(temp);

    /*
        Load walking sprites
    */
    walkDown = new Animation(5, downFrames);
    walkUp = new Animation(5, upFrames);
    walkLeft = new Animation(5, leftFrames);
    walkRight = new Animation(5, rightFrames);
    fighting = new Animation(7, fightingFrames);

    //load Attack buttons
    buttonAttack.load("images/ui/buttons/rock.png");

    //set attacks
    addAttack(Attack(nullptr, 10, 60));    
    addAttack(Attack(nullptr, 5, 60 * 2));    
    addAttack(Attack(nullptr, 5, 60 * 3));    

}

void Player::loadCamera(void* camera) {
    this->camera = camera;
}

void Player::drawAttackList() {
    /*
        Draw Button for attacks depending how much the player has
    */
    int leftX = ofGetWidth() / 2 - (int)(buttonAttack.getWidth() * attacks.size() / 2);
    for(unsigned int i = 0; i < attacks.size(); i++) {
        if(attackChoice == (int)i)
            ofSetColor(255, 255, 255);
        else
            ofSetColor(180, 180, 180);
        buttonAttack.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        buttonAttack.draw(leftX + i * buttonAttack.getWidth(), ofGetHeight() - buttonAttack.getHeight(), buttonAttack.getWidth(), buttonAttack.getWidth());
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

    int xpos = ofGetWidth() * (1.0 / 4.0) - fightingHitbox.getWidth()  / 2;
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
    health = 100;
}

Player::~Player() {
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}