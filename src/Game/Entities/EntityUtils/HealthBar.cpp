#include "HealthBar.h"

HealthBar::HealthBar()
{
    healthBar.load("images/ui/healthbar.png");
}

void HealthBar::drawHealthBar(int x, int y, int width, int height, int health, int maxHealth) {

    double healthRatio = (double)health / maxHealth;
    for (int i = 0; i < 3; i++) {
        if (healthRatio < 0)
            healthRatio = 0;
        else if (healthRatio < 0.33)
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        else if (healthRatio < 0.66)
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        else
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);

        ofDrawRectangle(x, y + healthBar.getHeight()/2 - 7, (int)(healthRatio * healthBar.getWidth()), 15);
    }
    ofFill();
    ofSetColor(255, 255, 255);

    healthBar.draw(x, y, width, height);
}