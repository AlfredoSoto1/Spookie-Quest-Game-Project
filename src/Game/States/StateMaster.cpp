#include "StateMaster.h"

StateMaster::StateMaster(Player* player) {
    this->player = player;
    this->player->getFightingHitBox().setRenderWidth(200);
    this->player->getFightingHitBox().setRenderHeight(200);
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
    } else if (currentState->getNextState() == CurrentState::PAUSED) {
        /*
            The new state will be the overworld
        */
        pauseState->setPastState(currentState);
        currentState = pauseState;
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
    this->pauseState = new PauseState();
    

    this->currentState = this->titleState;
}

void StateMaster::initAreas() {
    // vector<Entity*> entities;
    // ofPoint entrancePosition(1000, 1000);
    // Enemy *area2Enemy1 = new Enemy("enemy2", 30, 6, 4 * 120, 4 * 342);
    // Enemy *area2Enemy2 = new Enemy("enemy2", 30, 6, 4 * 254, 4 * 130);
    // Enemy *area2Enemy3 = new Enemy("enemy2", 30, 6, 4 * 542, 4 * 124);
    // Enemy *area2Enemy4 = new Enemy("enemy2", 30, 6, 4 * 532, 4 * 368);
    // Enemy *area2Enemy5 = new Enemy("enemy2", 30, 6, 4 * 266, 4 * 312);
    // Enemy *area2Enemy6 = new Enemy("enemy2", 30, 6, 4 * 194, 4 * 532);
    // entities.push_back(area2Enemy1);
    // entities.push_back(area2Enemy2);
    // entities.push_back(area2Enemy3);
    // entities.push_back(area2Enemy4);
    // entities.push_back(area2Enemy5);
    // entities.push_back(area2Enemy6);
    // Area* area2 = new Area("Area2", NULL, "images/areas/area2.png", "images/areas/area3_boundry.png", "audio/ice.wav", "images/stages/stage2.png", "images/areas/darkness.png", entrancePosition, entities);
    // generatedAreas.push_back(area2);

    ///-----------------------------------------------------------------------

    // vector<Entity*> entities1;
    // Enemy *monster = new Enemy("monster", 20, 4, 4 * 480, 4 * 432);

    // entities1.push_back(monster);
    
    // Boss* bossLevel2 = new Boss("Boss-1", 20, 4, 2, 1280, 720);
    // entities1.push_back(bossLevel2);

    // Friend* friend1 = new Friend("Friend-1", "", 1280, 720);
    // entities1.push_back(friend1);

    // Area* cave = new Area("cave", area2, "images/areas/area3.png", "images/areas/area3_boundry.png", "audio/forest.wav", "images/stages/stage1.png", "images/areas/darkness.png", entrancePosition, entities1);
    // generatedAreas.push_back(cave);
    // this->currentArea = cave;

    //------------------------------------------------------------------------
    
    string areaPath = "images/areas/area1.png";
    string areaBoundryPath = "images/areas/area1_boundry.png";
    string areaAudio = "audio/forest.wav";
    string areaFightingStage = "images/stages/stage1.png";
    string areaEffect = "images/areas/darkness.png";
    
    ofPoint entrancePosition(1679, 2003);
    vector<Entity*> tempEntityList;

    //load boss
    Boss* bossLevel1 = new Boss("Boss-1", 100, 4, 2, 870, 726);
    tempEntityList.push_back(bossLevel1);

    //load Enemies
    Enemy *mushroom1 = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, 1086, 1885);
    //enlarge image
    mushroom1->getHitBox().setRenderWidth(300);
    mushroom1->getHitBox().setRenderHeight(300);
    mushroom1->getFightingHitBox().setRenderWidth(600);
    mushroom1->getFightingHitBox().setRenderHeight(600);
    tempEntityList.push_back(mushroom1);
    
    Enemy *mushroom2 = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, 812, 1442);
    //enlarge image
    mushroom2->getHitBox().setRenderWidth(300);
    mushroom2->getHitBox().setRenderHeight(300);
    mushroom2->getFightingHitBox().setRenderWidth(600);
    mushroom2->getFightingHitBox().setRenderHeight(600);
    tempEntityList.push_back(mushroom2);

    Enemy *mushroom3 = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, 1954, 1075);
    //enlarge image
    mushroom3->getHitBox().setRenderWidth(300);
    mushroom3->getHitBox().setRenderHeight(300);
    mushroom3->getFightingHitBox().setRenderWidth(600);
    mushroom3->getFightingHitBox().setRenderHeight(600);
    tempEntityList.push_back(mushroom3);
    
    // load structure entities / inmovables
    // Structure* structure = new Structure("rock-1", "images/entities/inmovable/rock.png", 4 * 480, 4 * 470, 1);
    // entities2.push_back(structure);

    for(int i = 0; i < 10; i ++) {
        Structure* tree = new Structure("spruce", "images/entities/inmovable/pine_tree.png", 1370 + i * 100, 420 + ofRandom(-50, 50), 1);
        tree->getHitBox().setWidth(25);
        tree->getHitBox().setHeight(170);
        tree->getHitBox().setRenderWidth(80);
        tree->getHitBox().setRenderHeight(170);
        tempEntityList.push_back(tree);

        tree = new Structure("spruce", "images/entities/inmovable/pine_tree.png", 1370 + i * 100, 600 + ofRandom(-50, 50), 1);
        tree->getHitBox().setWidth(25);
        tree->getHitBox().setHeight(170);
        tree->getHitBox().setRenderWidth(80);
        tree->getHitBox().setRenderHeight(170);
        tempEntityList.push_back(tree);

        tree = new Structure("oak", "images/entities/inmovable/tree.png", 1170 + i * 100, 1716 + ofRandom(-100, 100), 1);
        tree->getHitBox().setWidth(40);
        tree->getHitBox().setHeight(170);
        tree->getHitBox().setRenderWidth(170);
        tree->getHitBox().setRenderHeight(170);
        tempEntityList.push_back(tree);

        tree = new Structure("oak", "images/entities/inmovable/tree.png", 1170 + i * 100, 1580 + ofRandom(-100, 100), 1);
        tree->getHitBox().setWidth(40);
        tree->getHitBox().setHeight(170);
        tree->getHitBox().setRenderWidth(170);
        tree->getHitBox().setRenderHeight(170);
        tempEntityList.push_back(tree);

        tree = new Structure("oak", "images/entities/inmovable/tree.png", 540 + i * 100, 1160 + ofRandom(-100, 100), 1);
        tree->getHitBox().setWidth(40);
        tree->getHitBox().setHeight(170);
        tree->getHitBox().setRenderWidth(170);
        tree->getHitBox().setRenderHeight(170);
        tempEntityList.push_back(tree);
    }

    Area* area1 = new Area("wild-life", nullptr, areaPath, areaBoundryPath, areaAudio, areaFightingStage, areaEffect, entrancePosition, tempEntityList);
    generatedAreas.push_back(area1);

    this->currentArea = area1;
}