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
        
        //checks if player is in a boss fight
        if(currentArea->inBossFight()) {
            //checks if has a next area
            if (currentArea->getNextArea() == nullptr) {
                //if it doesn't, reset everything after winning
                endGameState->setWin(true);
                currentState = endGameState;
                player->setHealth(player->getMaxHealth());//reset player's health
                for(Area* area : generatedAreas)
                    area->resetContent();
            } else {
                //if it has, go to next area
                currentArea = currentArea->getNextArea();
                overworldState->loadArea(currentArea);
                battleState->setStage(currentArea->getStage());
                currentState = winState;
            }
        }else {
            //if not in boss fight
            if(currentArea->getRemainingEnemies() == 0) {
                //start boss fight after no enemies are alive in area
                currentArea->setInBossFight(true);
                currentState = winState;
            }else {
                //if has enemies remaining, go back to state->
                currentState = winState;
            }
        }
    } else if (currentState->getNextState() == CurrentState::END) {
        /*
            This is called when Battle ends and player loses
        */
        currentState = endGameState;
        player->reset();
        for(Area* area : generatedAreas)
            area->resetContent();
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
    //prepare
    ofImage spawnImage;
    spawnImage.load("images/areas/area3_spawn.png");

    string areaPath = "images/areas/area3.png";
    string areaBoundryPath = "images/areas/area3_boundry.png";
    string areaAudio = "audio/forest.wav";
    string areaFightingStage = "images/stages/stage3.png";
    string areaEffect = "images/areas/darkness.png";
    
    ofPoint entrancePosition(570, 300);
    vector<Entity*> tempEntityList;

    for(int x = 0;x < spawnImage.getWidth(); x++) {
        for(int y = 0;y < spawnImage.getHeight(); y++) {
            ofColor spawnColor = spawnImage.getColor(x, y);
            if(spawnColor == ofColor::red) {
                Enemy *mushroom = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, x, y);
                //enlarge image
                mushroom->getHitBox().setRenderWidth(300);
                mushroom->getHitBox().setRenderHeight(300);
                mushroom->getFightingHitBox().setRenderWidth(600);
                mushroom->getFightingHitBox().setRenderHeight(600);
                tempEntityList.push_back(mushroom);
            }else if(spawnColor == ofColor::blue) {
                Boss* bossLevel2 = new Boss("Boss-2", 20, 4, 2, x, y);
                bossLevel2->getHitBox().setRenderWidth(300);
                bossLevel2->getHitBox().setRenderHeight(300);
                bossLevel2->getFightingHitBox().setRenderWidth(600);
                bossLevel2->getFightingHitBox().setRenderHeight(600);
                tempEntityList.push_back(bossLevel2);
            }
        }
    }

    Area* iceCave = new Area("ice-cave", nullptr, areaPath, areaBoundryPath, areaAudio, areaFightingStage, areaEffect, entrancePosition, tempEntityList);
    generatedAreas.push_back(iceCave);
    /*
        ---------------------------------------------------------
        prepare Area 2
    */
    tempEntityList.clear();
    spawnImage.load("images/areas/area2_spawn.png");

    areaPath = "images/areas/area2.png";
    areaBoundryPath = "images/areas/area2_boundry.png";
    areaAudio = "audio/forest.wav";
    areaFightingStage = "images/stages/stage2.png";
    areaEffect = "images/areas/darkness.png";
    
    entrancePosition = ofPoint(570, 300);

    for(int x = 0;x < spawnImage.getWidth(); x++) {
        for(int y = 0;y < spawnImage.getHeight(); y++) {
            ofColor spawnColor = spawnImage.getColor(x, y);
            if(spawnColor == ofColor::red) {
                Enemy *mushroom = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, x, y);
                //enlarge image
                mushroom->getHitBox().setRenderWidth(300);
                mushroom->getHitBox().setRenderHeight(300);
                mushroom->getFightingHitBox().setRenderWidth(600);
                mushroom->getFightingHitBox().setRenderHeight(600);
                tempEntityList.push_back(mushroom);
            }else if(spawnColor == ofColor::blue) {
                Boss* bossLevel2 = new Boss("Boss-2", 20, 4, 2, x, y);
                bossLevel2->getHitBox().setRenderWidth(300);
                bossLevel2->getHitBox().setRenderHeight(300);
                bossLevel2->getFightingHitBox().setRenderWidth(600);
                bossLevel2->getFightingHitBox().setRenderHeight(600);
                tempEntityList.push_back(bossLevel2);
            }
        }
    }

    Area* cave = new Area("cave", iceCave, areaPath, areaBoundryPath, areaAudio, areaFightingStage, areaEffect, entrancePosition, tempEntityList);
    generatedAreas.push_back(cave);

    /*
    -----------------------------------------------------------
        prepare Area 1
    */
    tempEntityList.clear();
    spawnImage.load("images/areas/area1_spawn.png");

    areaPath = "images/areas/area1.png";
    areaBoundryPath = "images/areas/area1_boundry.png";
    areaAudio = "audio/forest.wav";
    areaFightingStage = "images/stages/stage1.png";
    areaEffect = "images/areas/darkness.png";

    for(int x = 0;x < spawnImage.getWidth(); x++) {
        for(int y = 0;y < spawnImage.getHeight(); y++) {
            ofColor spawnColor = spawnImage.getColor(x, y);
            if(spawnColor == ofColor::red) {
                Enemy *mushroom = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, x, y);
                //enlarge image
                mushroom->getHitBox().setRenderWidth(300);
                mushroom->getHitBox().setRenderHeight(300);
                mushroom->getFightingHitBox().setRenderWidth(600);
                mushroom->getFightingHitBox().setRenderHeight(600);
                tempEntityList.push_back(mushroom);
                
                // Enemy *goblin = new Enemy("golbin", EnemyE::GOBLIN, 20, 4, x, y);
                // //enlarge image
                // goblin->getHitBox().setRenderWidth(300);
                // goblin->getHitBox().setRenderHeight(300);
                // goblin->getFightingHitBox().setRenderWidth(600);
                // goblin->getFightingHitBox().setRenderHeight(600);
                // tempEntityList.push_back(goblin);

            }else if(spawnColor == ofColor::blue) {
                Boss* bossLevel1 = new Boss("Boss-1", 20, 4, 2, x, y);
                bossLevel1->getHitBox().setRenderWidth(300);
                bossLevel1->getHitBox().setRenderHeight(300);
                bossLevel1->getFightingHitBox().setRenderWidth(600);
                bossLevel1->getFightingHitBox().setRenderHeight(600);
                tempEntityList.push_back(bossLevel1);
            }else if(spawnColor == ofColor::white) {
                int random = ofRandom(0, 1);
                if(random == 0) {
                    Structure* tree = new Structure("spruce", "images/entities/inmovable/tree_0.png", x, y, 1);
                    tree->getHitBox().setWidth(25);
                    tree->getHitBox().setHeight(170);
                    tree->getHitBox().setRenderWidth(80);
                    tree->getHitBox().setRenderHeight(170);
                    tempEntityList.push_back(tree);
                }else {
                    Structure* tree = new Structure("oak", "images/entities/inmovable/tree_1.png", x, y, 1);
                    tree->getHitBox().setWidth(40);
                    tree->getHitBox().setHeight(170);
                    tree->getHitBox().setRenderWidth(170);
                    tree->getHitBox().setRenderHeight(170);
                    tempEntityList.push_back(tree);
                }
            }
        }
    }

    entrancePosition = ofPoint(1679, 2003);

    Area* area1 = new Area("wild-life", cave, areaPath, areaBoundryPath, areaAudio, areaFightingStage, areaEffect, entrancePosition, tempEntityList);
    generatedAreas.push_back(area1);


    //set this current area to last area (which is the first one)
    this->currentArea = area1;
}