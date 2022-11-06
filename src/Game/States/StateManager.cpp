#include "StateManager.h"

#include "ofMain.h"

StateManager::StateManager(Player* player) {
    this->player = player;
    initAreas();
    createStates();
}

StateManager::~StateManager() {
    //delete the pointers created
    // in *this class
    for(Area* area : generatedAreas)
        delete area;

    delete titleState;
    delete overworldState;
    delete battleState;
    delete winState;
    delete endGameState;
}

State& StateManager::getCurrentState() {
    return *currentState;
}

void StateManager::update() {
    currentState->update();
    
    if(!currentState->hasFinished())
        return;

    //Toggles music when current state finishes
    currentState->toggleMusic();

    if (currentState->getNextState() == CurrentState::TITLE) {
        /*
            Prepares areas for the upcomming state
            when being on Title
        */
        endGameState->setWin(false);
        for(Area* area : generatedAreas)
            area->resetEnemies();
        currentArea = generatedAreas.at(generatedAreas.size()-1);
        battleState->reset();
        battleState->setStage(currentArea->getStage());
        overworldState->loadArea(currentArea);
        currentState = titleState;

    } else if (currentState->getNextState() == CurrentState::OVERWORLD) {
        /*
            The new state will be the overworld
        */
        currentState = overworldState;

    } else if (currentState->getNextState() == CurrentState::BATTLE) {
        /*
            The new state will be Battle, this being called after overworld state
        */
        battleState->startBattle(overworldState->getEnemyToBattle());
        currentState = battleState;

    } else if (currentState->getNextState() == CurrentState::WIN) {
        /*
            This is called when Battle ends and player wins
        */
        Enemy* enemy = overworldState->getEnemyToBattle();
        enemy->kill();
        if (currentArea->getRemainingEnemies() == 0) {
            if(!currentArea->inBossFight()) {
                currentArea->setInBossFight(true);
                currentState = winState;
            }else if (currentArea->getNextArea() == nullptr) {
                endGameState->setWin(true);
                currentState = endGameState;
            } else {
                currentArea = currentArea->getNextArea();
                overworldState->loadArea(currentArea);
                battleState->setStage(currentArea->getStage());
                currentState = winState;
            }
        } else if(currentArea->inBossFight()) {
            currentArea = currentArea->getNextArea();
            overworldState->loadArea(currentArea);
            battleState->setStage(currentArea->getStage());
            currentState = winState;
        }else {
            currentState = winState;
        }

    } else if (currentState->getNextState() == CurrentState::END) {
        /*
            This is called when Battle ends and player loses
        */
        currentState = endGameState;
        player->reset();
    }
    /*
        Toggles music again and resets the current state
    */
    currentState->toggleMusic();
    currentState->reset();
}

void StateManager::draw() {
    currentState->draw();
}

void StateManager::createStates() {
    this->titleState = new TitleState();
    this->overworldState = new OverworldState(this->player, this->currentArea);
    this->battleState = new BattleState(this->player, this->currentArea);
    this->winState = new WinState();
    this->endGameState = new EndGameState();

    this->currentState = this->titleState;
}

void StateManager::initAreas() {
    vector<Entity*> enemies2;
    ofPoint entrancePosition2(4 * 110, 4 * 116);
    Enemy *area2Enemy1 = new Enemy("enemy2", 30, 6, 4 * 120, 4 * 342);
    Enemy *area2Enemy2 = new Enemy("enemy2", 30, 6, 4 * 254, 4 * 130);
    Enemy *area2Enemy3 = new Enemy("enemy2", 30, 6, 4 * 542, 4 * 124);
    Enemy *area2Enemy4 = new Enemy("enemy2", 30, 6, 4 * 532, 4 * 368);
    Enemy *area2Enemy5 = new Enemy("enemy2", 30, 6, 4 * 266, 4 * 312);
    Enemy *area2Enemy6 = new Enemy("enemy2", 30, 6, 4 * 194, 4 * 532);
    enemies2.push_back(area2Enemy1);
    enemies2.push_back(area2Enemy2);
    enemies2.push_back(area2Enemy3);
    enemies2.push_back(area2Enemy4);
    enemies2.push_back(area2Enemy5);
    enemies2.push_back(area2Enemy6);
    Area* area2 = new Area("Area2", NULL, "images/areas/area2.png", "audio/ice.wav", "images/stages/stage2.png", entrancePosition2, enemies2);
    generatedAreas.push_back(area2);

    
    vector<Entity*> enemies1;
    ofPoint entrancePosition1(4 * 414, 4 * 566);
    Enemy *area1Enemy1 = new Enemy("enemy1", 20, 4, 4 * 480, 4 * 432);
    // Enemy *area1Enemy2 = new Enemy("enemy1", 20, 4, 4 * 225, 4 * 178);
    // Enemy *area1Enemy3 = new Enemy("enemy1", 20, 4, 4 * 420, 4 * 178);

    enemies1.push_back(area1Enemy1);
    // enemies1.push_back(area1Enemy2);
    // enemies1.push_back(area1Enemy3);
    
    Boss* bossLevel1 = new Boss("Boss-1", 20, 4, 2, 1280, 720);
    enemies1.push_back(bossLevel1);

    Rock* rock = new Rock("rock-1", 4 * 480, 4 * 470, 1);
    enemies1.push_back(rock);

    Area* area1 = new Area("Area1", area2, "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1);
    
    generatedAreas.push_back(area1);

    this->currentArea = area1;
}