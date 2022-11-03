#pragma once

#ifndef HEALTH_BAR_HEADER
#define HEALTH_BAR_HEADER

#include "ofMain.h"

class HealthBar {
public:
    HealthBar();

    void drawHealthBar(int x, int y, int width, int height, int health, int maxHealth);

private:
    int maxHealth;
    int currentHealth;

    ofImage healthBar;
};

#endif