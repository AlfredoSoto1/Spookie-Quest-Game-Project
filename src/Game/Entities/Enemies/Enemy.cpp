#include "Enemy.h"
#include "OverworldCamera.h"

Enemy::Enemy(const string& name, EnemyE type, int health, int baseDamage, int ox, int oy) : 
    EntityFighter(name, HitBox(ox, oy, 50, 64), HitBox(420, 220, 97, 125), health, baseDamage)
{
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    vector<ofImage> idleLeftFrames;
    vector<ofImage> idleRightFrames;
    vector<ofImage> deathFrames;
    vector<ofImage> hitFrames;

    if(type == EnemyE::MUSHROOM) {
        obtainFramesOf(&rightFrames    , 8, 150, 150, "images/entities/enemy/Mushroom/Run_right.png");
        obtainFramesOf(&leftFrames     , 8, 150, 150, "images/entities/enemy/Mushroom/Run_left.png");
        obtainFramesOf(&idleRightFrames, 4, 150, 150, "images/entities/enemy/Mushroom/Idle_right.png");
        obtainFramesOf(&idleLeftFrames , 4, 150, 150, "images/entities/enemy/Mushroom/Idle_left.png");
        obtainFramesOf(&deathFrames    , 4, 150, 150, "images/entities/enemy/Mushroom/Death.png");
        obtainFramesOf(&hitFrames      , 4, 150, 150, "images/entities/enemy/Mushroom/Hit.png");

        //attack frames
        vector<ofImage> attack1;
        vector<ofImage> attack2;
        vector<ofImage> attack3;
        obtainFramesOf(&attack1      , 8 , 150, 150, "images/entities/enemy/Mushroom/Attack1.png");
        obtainFramesOf(&attack2      , 8 , 150, 150, "images/entities/enemy/Mushroom/Attack2.png");
        obtainFramesOf(&attack3      , 11, 150, 150, "images/entities/enemy/Mushroom/Attack3.png");

        vector<ofImage> projectile;
        obtainFramesOf(&projectile, 8, 50, 50, "images/entities/enemy/Mushroom/projectile.png");

        addAttack(Attack(new Animation(4, attack1), new Animation(3, projectile), 4, 90, 60));
        addAttack(Attack(new Animation(4, attack2), 6, 90));
        addAttack(Attack(new Animation(4, attack3), 8, 90));
    } else if(type == EnemyE::GOBLIN) {

        obtainFramesOf(&rightFrames    , 8, 150, 150, "images/entities/enemy/Goblin/Run_right.png");
        obtainFramesOf(&leftFrames     , 8, 150, 150, "images/entities/enemy/Goblin/Run_left.png");
        obtainFramesOf(&idleRightFrames, 4, 150, 150, "images/entities/enemy/Goblin/Idle_right.png");
        obtainFramesOf(&idleLeftFrames , 4, 150, 150, "images/entities/enemy/Goblin/Idle_left.png");
        obtainFramesOf(&deathFrames    , 4, 150, 150, "images/entities/enemy/Goblin/Death.png");
        obtainFramesOf(&hitFrames      , 4, 150, 150, "images/entities/enemy/Goblin/Hit.png");

        //attack frames
        vector<ofImage> attack1;
        vector<ofImage> attack2;
        vector<ofImage> attack3;
        obtainFramesOf(&attack1      , 8 , 150, 150, "images/entities/enemy/Goblin/Attack1.png");
        obtainFramesOf(&attack2      , 8 , 150, 150, "images/entities/enemy/Goblin/Attack2.png");
        obtainFramesOf(&attack3      , 11, 150, 150, "images/entities/enemy/Goblin/Attack3.png");
        
        vector<ofImage> projectile;
        obtainFramesOf(&projectile, 19, 100, 100, "images/entities/enemy/Goblin/projectile.png");
        
        addAttack(Attack(new Animation(4, attack1), 4, 90));
        addAttack(Attack(new Animation(4, attack2), 6, 90));
        addAttack(Attack(new Animation(4, attack3), new Animation(3, projectile), 8, 90, 60));
    }else if(type == EnemyE::SKELETON) {

        obtainFramesOf(&rightFrames    , 4, 150, 150, "images/entities/enemy/Skeleton/Run_right.png");
        obtainFramesOf(&leftFrames     , 4, 150, 150, "images/entities/enemy/Skeleton/Run_left.png");
        obtainFramesOf(&idleRightFrames, 4, 150, 150, "images/entities/enemy/Skeleton/Idle_right.png");
        obtainFramesOf(&idleLeftFrames , 4, 150, 150, "images/entities/enemy/Skeleton/Idle_left.png");
        obtainFramesOf(&deathFrames    , 4, 150, 150, "images/entities/enemy/Skeleton/Death.png");
        obtainFramesOf(&hitFrames      , 4, 150, 150, "images/entities/enemy/Skeleton/Hit.png");

        //attack frames
        vector<ofImage> attack1;
        vector<ofImage> attack2;
        vector<ofImage> attack3;
        obtainFramesOf(&attack1      , 8 , 150, 150, "images/entities/enemy/Skeleton/Attack1.png");
        obtainFramesOf(&attack2      , 8 , 150, 150, "images/entities/enemy/Skeleton/Attack2.png");
        obtainFramesOf(&attack3      , 6 , 150, 150, "images/entities/enemy/Skeleton/Attack3.png");

        vector<ofImage> projectile;
        obtainFramesOf(&projectile, 8, 92, 92, "images/entities/enemy/Skeleton/projectile.png");

        addAttack(Attack(new Animation(4, attack1), 4, 90));
        addAttack(Attack(new Animation(4, attack2), 6, 90));
        addAttack(Attack(new Animation(4, attack3), new Animation(3, projectile), 8, 90, 60));
    }else if(type == EnemyE::EVIL_WIZZARD) {

        obtainFramesOf(&rightFrames    , 8, 150, 150, "images/entities/enemy/evilWizzard/Run_right.png");
        obtainFramesOf(&leftFrames     , 8, 150, 150, "images/entities/enemy/evilWizzard/Run_left.png");
        obtainFramesOf(&idleRightFrames, 8, 150, 150, "images/entities/enemy/evilWizzard/Idle_right.png");
        obtainFramesOf(&idleLeftFrames , 8, 150, 150, "images/entities/enemy/evilWizzard/Idle_left.png");
        obtainFramesOf(&deathFrames    , 5, 150, 150, "images/entities/enemy/evilWizzard/Death.png");
        obtainFramesOf(&hitFrames      , 4, 150, 150, "images/entities/enemy/evilWizzard/Hit.png");

        //attack frames
        vector<ofImage> attack1;
        obtainFramesOf(&attack1      , 8 , 150, 150, "images/entities/enemy/evilWizzard/Attack.png");
        
        addAttack(Attack(new Animation(4, attack1), 4, 90));
    } else if(type == EnemyE::FIRE_WORM) {
        obtainFramesOf(&rightFrames    , 9, 90, 90, "images/entities/enemy/fireWorm/Run_right.png");
        obtainFramesOf(&leftFrames     , 9, 90, 90, "images/entities/enemy/fireWorm/Run_left.png");
        obtainFramesOf(&idleRightFrames, 9, 90, 90, "images/entities/enemy/fireWorm/Idle_right.png");
        obtainFramesOf(&idleLeftFrames , 9, 90, 90, "images/entities/enemy/fireWorm/Idle_left.png");
        obtainFramesOf(&deathFrames    , 8, 90, 90, "images/entities/enemy/fireWorm/Death.png");
        obtainFramesOf(&hitFrames      , 3, 90, 90, "images/entities/enemy/fireWorm/Hit.png");

        //attack frames
        vector<ofImage> attack1;
        obtainFramesOf(&attack1      , 16 , 90, 90, "images/entities/enemy/fireWorm/Attack1.png");

        vector<ofImage> projectile;
        obtainFramesOf(&projectile, 6, 46, 46, "images/entities/enemy/fireWorm/projectile.png");

        addAttack(Attack(new Animation(4, attack1), new Animation(3, projectile), 8, 60, 60));
    } else if(type == EnemyE::DARK_WIZZARD) {
        obtainFramesOf(&rightFrames    , 8, 250, 250, "images/entities/enemy/darkWizzard/Run_right.png");
        obtainFramesOf(&leftFrames     , 8, 250, 250, "images/entities/enemy/darkWizzard/Run_left.png");
        obtainFramesOf(&idleRightFrames, 8, 250, 250, "images/entities/enemy/darkWizzard/Idle_right.png");
        obtainFramesOf(&idleLeftFrames , 8, 250, 250, "images/entities/enemy/darkWizzard/Idle_left.png");
        obtainFramesOf(&deathFrames    , 7, 250, 250, "images/entities/enemy/darkWizzard/Death.png");
        obtainFramesOf(&hitFrames      , 3, 250, 250, "images/entities/enemy/darkWizzard/Hit.png");

        //attack frames
        vector<ofImage> attack1;
        vector<ofImage> attack2;
        obtainFramesOf(&attack1      , 8 , 250, 250, "images/entities/enemy/darkWizzard/Attack1.png");
        obtainFramesOf(&attack2      , 8 , 250, 250, "images/entities/enemy/darkWizzard/Attack2.png");

        addAttack(Attack(new Animation(4, attack1), 8, 60));
        addAttack(Attack(new Animation(4, attack2), 8, 60));
    }else if(type == EnemyE::FLYING_EYE) {
        obtainFramesOf(&rightFrames    , 8, 150, 150, "images/entities/enemy/flyingEye/Run_right.png");
        obtainFramesOf(&leftFrames     , 8, 150, 150, "images/entities/enemy/flyingEye/Run_left.png");
        obtainFramesOf(&idleRightFrames, 8, 150, 150, "images/entities/enemy/flyingEye/Run_right.png");
        obtainFramesOf(&idleLeftFrames , 8, 150, 150, "images/entities/enemy/flyingEye/Run_left.png");
        obtainFramesOf(&deathFrames    , 4, 150, 150, "images/entities/enemy/flyingEye/Death.png");
        obtainFramesOf(&hitFrames      , 4, 150, 150, "images/entities/enemy/flyingEye/Hit.png");

        //attack frames
        vector<ofImage> attack1;
        vector<ofImage> attack2;
        vector<ofImage> attack3;
        obtainFramesOf(&attack1      , 8 , 150, 150, "images/entities/enemy/flyingEye/Attack1.png");
        obtainFramesOf(&attack2      , 8 , 150, 150, "images/entities/enemy/flyingEye/Attack2.png");
        obtainFramesOf(&attack3      , 6 , 150, 150, "images/entities/enemy/flyingEye/Attack3.png");

        vector<ofImage> projectile;
        obtainFramesOf(&projectile, 8, 48, 48, "images/entities/enemy/flyingEye/projectile.png");

        addAttack(Attack(new Animation(4, attack1), new Animation(3, projectile), 8, 60, 60));
        addAttack(Attack(new Animation(4, attack2), new Animation(3, projectile), 8, 60, 60));
        addAttack(Attack(new Animation(4, attack3), new Animation(3, projectile), 8, 60, 60));
    }

    /*
        required animations
    */
    walkLeft = new Animation(5, leftFrames);
    walkRight = new Animation(5, rightFrames);
    idleRight = new Animation(5, idleRightFrames);
    idleLeft = new Animation(5, idleLeftFrames);

    fighting = new Animation(7, idleLeftFrames);

    hit = new Animation(4, hitFrames);

    death = new Animation(10, deathFrames);
    death->setShowOnce(true);

    speed = 8;
    movingTime = 15;
    standingStillTime = 50;
    timeDirectionCounter = glm::vec2(0.0, 0.0);
    movementDirection = glm::vec2(0.0, 0.0);
    hitbox.setDirection(Direction::up);
    
}

Enemy::~Enemy() {
    delete walkLeft;
    delete walkRight;
    delete idleRight;
    delete idleLeft;

    delete fighting;

    delete death;
    delete hit;

    vector<Attack>& attacks = getAttacks();
    for(unsigned int i = 0;i < attacks.size(); i++) {
        delete attacks[i].getAnimation();
        if(attacks[i].hasProjectile())
            delete attacks[i].getProjectileAnimation();
    }
}

void Enemy::obtainFramesOf(vector<ofImage>* frames, int frameCount, int imgWidth, int imgHeight, const string& path) {
    ofImage sprite;
    ofImage temp;
    sprite.load(path);
    for(int i = 0; i < frameCount; i++) {
        temp.cropFrom(sprite, (frameCount - 1 - i) * imgWidth, 0, imgWidth, imgHeight);
        frames->push_back(temp);
    }
}

Animation* Enemy::getHit() {
    return hit;
}

Animation* Enemy::getDeath() {
    return death;
}

bool Enemy::isDead() { 
    return dead; 
}

void Enemy::kill() {
    this->dead = true;
    this->health = 0;
}

void Enemy::revive() {
    this->dead = false;
    this->health = maxHealth;
}

ofImage Enemy::getSprite() {
    return overworldSprite; 
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

void Enemy::inOverworldDraw(void* camera) {
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

void Enemy::fightingUpdate() {
    fightingSprite = fighting->getCurrentFrame();
    fighting->update();

    int xpos = ofGetWidth() * (3.0 / 4.0) - fightingHitbox.getWidth()  / 2;
    int ypos = ofGetHeight() * (1.0 / 2.0) - fightingHitbox.getHeight() / 2;

    fightingHitbox.setX(xpos);
    fightingHitbox.setY(ypos);
}

void Enemy::reset() {
}
