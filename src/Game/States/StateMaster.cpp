#include "StateMaster.h"

StateMaster::StateMaster(Player* player) {
    this->player = player;
    initAreas();
    createStates();
}

StateMaster::~StateMaster() {
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

State& StateMaster::getCurrentState() {
    return *currentState;
}

void StateMaster::update() {
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

void StateMaster::draw() {
    currentState->draw();
}

void StateMaster::createStates() {
    this->titleState = new TitleState();
    this->overworldState = new OverworldState(this->player, this->currentArea);
    this->battleState = new BattleState(this->player, this->currentArea);
    this->winState = new WinState();
    this->endGameState = new EndGameState();

    this->currentState = this->titleState;
}

void StateMaster::initAreas() {
    vector<Entity*> entities;
    ofPoint entrancePosition(1000, 1000);
    Enemy *area2Enemy1 = new Enemy("enemy2", 30, 6, 4 * 120, 4 * 342);
    Enemy *area2Enemy2 = new Enemy("enemy2", 30, 6, 4 * 254, 4 * 130);
    Enemy *area2Enemy3 = new Enemy("enemy2", 30, 6, 4 * 542, 4 * 124);
    Enemy *area2Enemy4 = new Enemy("enemy2", 30, 6, 4 * 532, 4 * 368);
    Enemy *area2Enemy5 = new Enemy("enemy2", 30, 6, 4 * 266, 4 * 312);
    Enemy *area2Enemy6 = new Enemy("enemy2", 30, 6, 4 * 194, 4 * 532);
    entities.push_back(area2Enemy1);
    entities.push_back(area2Enemy2);
    entities.push_back(area2Enemy3);
    entities.push_back(area2Enemy4);
    entities.push_back(area2Enemy5);
    entities.push_back(area2Enemy6);
    Area* area2 = new Area("Area2", NULL, "images/areas/area2.png", "audio/ice.wav", "images/stages/stage2.png", entrancePosition, entities);
    generatedAreas.push_back(area2);

    ///-----------------------------------------------------------------------

    vector<Entity*> entities1;
    Enemy *monster = new Enemy("monster", 20, 4, 4 * 480, 4 * 432);

    entities1.push_back(monster);
    
    Boss* bossLevel2 = new Boss("Boss-1", 20, 4, 2, 1280, 720);
    entities1.push_back(bossLevel2);

    Area* cave = new Area("cave", area2, "images/areas/area3.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition, entities1);
    generatedAreas.push_back(cave);

    //------------------------------------------------------------------------
    
    vector<Entity*> entities2;
    Enemy *enemy1 = new Enemy("enemy1", 20, 4, 4 * 480, 4 * 432);

    entities2.push_back(enemy1);
    
    Boss* bossLevel1 = new Boss("Boss-1", 20, 4, 2, 1280, 720);
    entities2.push_back(bossLevel1);

    Structure* structure = new Structure("rock-1", "images/entities/inmovable/rock.png", 4 * 480, 4 * 470, 1);
    entities2.push_back(structure);

    int xLoc = 1500;
    int yLoc = 1500;
    int radius = 800;
    for(int i = 0; i < 5; i ++) {
        Structure* tree = new Structure("spruce", "images/entities/inmovable/pine_tree.png", xLoc + ofRandom(-radius, radius), yLoc + ofRandom(-radius, radius), 1);
        tree->getHitBox().setWidth(25);
        tree->getHitBox().setHeight(100);
        tree->getHitBox().setRenderWidth(80);
        tree->getHitBox().setRenderHeight(170);
        entities2.push_back(tree);

        tree = new Structure("oak", "images/entities/inmovable/tree.png", xLoc + ofRandom(-radius, radius), yLoc + ofRandom(-radius, radius), 1);
        tree->getHitBox().setWidth(40);
        tree->getHitBox().setHeight(100);
        tree->getHitBox().setRenderWidth(170);
        tree->getHitBox().setRenderHeight(170);
        entities2.push_back(tree);

        tree = new Structure("cutted tree", "images/entities/inmovable/cutted_tree.png", xLoc + ofRandom(-radius, radius), yLoc + ofRandom(-radius, radius), 1);
        tree->getHitBox().setWidth(50);
        tree->getHitBox().setHeight(50);
        tree->getHitBox().setRenderWidth(67);
        tree->getHitBox().setRenderHeight(100);
        entities2.push_back(tree);

        tree = new Structure("dead tree", "images/entities/inmovable/dead_tree.png", xLoc + ofRandom(-radius, radius), yLoc + ofRandom(-radius, radius), 1);
        tree->getHitBox().setWidth(50);
        tree->getHitBox().setHeight(50);
        tree->getHitBox().setRenderWidth(100);
        tree->getHitBox().setRenderHeight(200);
        entities2.push_back(tree);
    }

    Area* area1 = new Area("wild-life", cave, "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition, entities2);
    generatedAreas.push_back(area1);

    this->currentArea = area1;
}