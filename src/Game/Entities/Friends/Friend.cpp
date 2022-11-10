#include "Friend.h"
#include "OverworldCamera.h"

Friend::Friend(const string& name, const string& path, int ox, int oy)
    : Entity(name, HitBox(ox, oy, 100, 100), 100)
{
    overworldSprite.load(path);
}

void Friend::interact() {
    //friend interaction here
}

void Friend::inOverworldUpdate() {
    //update here
}

void Friend::inOverworldDraw(void* camera) {
    // OverworldCamera* cameraPtr = static_cast<OverworldCamera*>(camera);

    //draw friend here
}