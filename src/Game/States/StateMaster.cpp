#include "StateMaster.h"

StateMaster::StateMaster(Player* player) {
    this->player = player;
    this->player->getFightingHitBox().setRenderWidth(450);
    this->player->getFightingHitBox().setRenderHeight(300);
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
            if(currentArea->inBossFight()) {
                if (currentArea->getNextArea() == nullptr) {
                    endGameState->setWin(true);
                    currentState = endGameState;
                    player->setHealth(player->getMaxHealth());//reset player's health
                    for(Area* area : generatedAreas)
                        area->resetContent();
                } else {
                    currentArea = currentArea->getNextArea();
                    overworldState->loadArea(currentArea);
                    battleState->setStage(currentArea->getStage());
                    currentState = winState;
                }
            } else {
                currentArea->setInBossFight(true);
                currentState = winState;
            }
        }else {
            Boss* boss = dynamic_cast<Boss*>(enemy);
            if(currentArea->inBossFight() && boss != nullptr) {
                if (currentArea->getNextArea() == nullptr) {
                    endGameState->setWin(true);
                    currentState = endGameState;
                    player->setHealth(player->getMaxHealth());//reset player's health
                    for(Area* area : generatedAreas)
                        area->resetContent();
                } else {
                    currentArea = currentArea->getNextArea();
                    overworldState->loadArea(currentArea);
                    battleState->setStage(currentArea->getStage());
                    currentState = winState;
                }
            } else {
                currentState = winState;
            } 
        }
    } else if (currentState->getNextState() == CurrentState::END) {
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
    ofImage spawnImage1;
    spawnImage1.load("images/areas/area3_spawn.png");

    string areaPath1             = "images/areas/area3.png";
    string areaBoundryPath1      = "images/areas/area3_boundry.png";
    string areaAudio1            = "audio/forest.wav";
    string areaFightingStage1    = "images/stages/stage3.png";
    string areaEffect1           = "images/areas/darkness_1.png";
    
    ofPoint entrancePosition1(570, 300);
    vector<Entity*> tempEntityList1;

    for(int x = 0;x < spawnImage1.getWidth(); x++) {
        for(int y = 0;y < spawnImage1.getHeight(); y++) {
            ofColor spawnColor = spawnImage1.getColor(x, y);
            if(spawnColor == ofColor::red) {
                Enemy *mushroom = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, x, y);
                //enlarge image
                mushroom->getHitBox().setRenderWidth(300);
                mushroom->getHitBox().setRenderHeight(300);
                mushroom->getFightingHitBox().setRenderWidth(600);
                mushroom->getFightingHitBox().setRenderHeight(600);
                tempEntityList1.push_back(mushroom);
            }else if(spawnColor == ofColor::blue) {
                Boss* bossLevel3 = new Boss("Boss-3", 20, 4, 2, x, y);
                bossLevel3->getHitBox().setRenderWidth(300);
                bossLevel3->getHitBox().setRenderHeight(300);
                bossLevel3->getFightingHitBox().setRenderWidth(600);
                bossLevel3->getFightingHitBox().setRenderHeight(600);
                tempEntityList1.push_back(bossLevel3);
            }
        }
    }

    Area* iceCave = new Area("ice-cave", nullptr, areaPath1, areaBoundryPath1, areaAudio1, areaFightingStage1, areaEffect1, entrancePosition1, tempEntityList1);
    generatedAreas.push_back(iceCave);
    // this->currentArea = iceCave;
    /*
        ---------------------------------------------------------
        prepare Area 2
    */
    ofImage spawnImage2;
    spawnImage2.load("images/areas/area2_spawn.png");

    string areaPath2            = "images/areas/area2.png";
    string areaBoundryPath2     = "images/areas/area2_boundry.png";
    string areaAudio2           = "audio/forest.wav";
    string areaFightingStage2   = "images/stages/stage2.png";
    string areaEffect2          = "images/areas/darkness_1.png";
    
    ofPoint entrancePosition2(570, 300);
    vector<Entity*> tempEntityList2;

    for(int x = 0;x < spawnImage2.getWidth(); x++) {
        for(int y = 0;y < spawnImage2.getHeight(); y++) {
            ofColor spawnColor = spawnImage2.getColor(x, y);
            if(spawnColor == ofColor::red) {
                // Enemy *mushroom = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, x, y);
                // //enlarge image
                // mushroom->getHitBox().setRenderWidth(300);
                // mushroom->getHitBox().setRenderHeight(300);
                // mushroom->getFightingHitBox().setRenderWidth(600);
                // mushroom->getFightingHitBox().setRenderHeight(600);
                // tempEntityList2.push_back(mushroom);
                int random = ofRandom(2);
                if(random == 0) {
                    Enemy *mushroom = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, x, y);
                    //enlarge image
                    mushroom->getHitBox().setRenderWidth(300);
                    mushroom->getHitBox().setRenderHeight(300);
                    mushroom->getFightingHitBox().setRenderWidth(600);
                    mushroom->getFightingHitBox().setRenderHeight(600);
                    tempEntityList2.push_back(mushroom);

                }else {
                    Enemy *goblin = new Enemy("golbin", EnemyE::GOBLIN, 20, 4, x, y);
                    //enlarge image
                    goblin->getHitBox().setRenderWidth(300);
                    goblin->getHitBox().setRenderHeight(300);
                    goblin->getFightingHitBox().setRenderWidth(600);
                    goblin->getFightingHitBox().setRenderHeight(600);
                    tempEntityList2.push_back(goblin);
                }
            }else if(spawnColor == ofColor::blue) {
                Boss* bossLevel2 = new Boss("Boss-2", 20, 4, 2, x, y);
                bossLevel2->getHitBox().setRenderWidth(300);
                bossLevel2->getHitBox().setRenderHeight(300);
                bossLevel2->getFightingHitBox().setRenderWidth(600);
                bossLevel2->getFightingHitBox().setRenderHeight(600);
                tempEntityList2.push_back(bossLevel2);
            }
        }
    }

    Area* cave = new Area("cave", iceCave, areaPath2, areaBoundryPath2, areaAudio2, areaFightingStage2, areaEffect2, entrancePosition2, tempEntityList2);
    generatedAreas.push_back(cave);

    /*
    -----------------------------------------------------------
        prepare Area 1
    */
    ofImage spawnImage3;
    spawnImage3.load("images/areas/area1_spawn.png");

    string areaPath3            = "images/areas/area1.png";
    string areaBoundryPath3     = "images/areas/area1_boundry.png";
    string areaAudio3           = "audio/forest.wav";
    string areaFightingStage3   = "images/stages/stage1.png";
    string areaEffect3          = "images/areas/darkness_1.png";

    vector<Entity*> tempEntityList3;

    for(int x = 0;x < spawnImage3.getWidth(); x++) {
        for(int y = 0;y < spawnImage3.getHeight(); y++) {
            ofColor spawnColor = spawnImage3.getColor(x, y);
            if(spawnColor == ofColor::red) {
                 Enemy *goblin = new Enemy("golbin", EnemyE::SKELETON, 20, 4, x, y);
                //enlarge image
                goblin->getHitBox().setRenderWidth(300);
                goblin->getHitBox().setRenderHeight(300);
                goblin->getFightingHitBox().setRenderWidth(600);
                goblin->getFightingHitBox().setRenderHeight(600);
                tempEntityList3.push_back(goblin);
                // int random = ofRandom(3);
                // if(random == 0) {
                //     Enemy *mushroom = new Enemy("mushroom", EnemyE::MUSHROOM, 20, 4, x, y);
                //     //enlarge image
                //     mushroom->getHitBox().setRenderWidth(300);
                //     mushroom->getHitBox().setRenderHeight(300);
                //     mushroom->getFightingHitBox().setRenderWidth(600);
                //     mushroom->getFightingHitBox().setRenderHeight(600);
                //     tempEntityList3.push_back(mushroom);

                // }else if(random == 1){
                //     Enemy *goblin = new Enemy("golbin", EnemyE::GOBLIN, 20, 4, x, y);
                //     //enlarge image
                //     goblin->getHitBox().setRenderWidth(300);
                //     goblin->getHitBox().setRenderHeight(300);
                //     goblin->getFightingHitBox().setRenderWidth(600);
                //     goblin->getFightingHitBox().setRenderHeight(600);
                //     tempEntityList3.push_back(goblin);
                // }else if(random == 2){
                //     Enemy *goblin = new Enemy("skeleton", EnemyE::SKELETON, 20, 4, x, y);
                //     //enlarge image
                //     goblin->getHitBox().setRenderWidth(300);
                //     goblin->getHitBox().setRenderHeight(300);
                //     goblin->getFightingHitBox().setRenderWidth(600);
                //     goblin->getFightingHitBox().setRenderHeight(600);
                //     tempEntityList3.push_back(goblin);
                // }
            }else if(spawnColor == ofColor::blue) {
                Boss* bossLevel1 = new Boss("Boss-1", 20, 4, 2, x, y);
                bossLevel1->getHitBox().setRenderWidth(300);
                bossLevel1->getHitBox().setRenderHeight(300);
                bossLevel1->getFightingHitBox().setRenderWidth(600);
                bossLevel1->getFightingHitBox().setRenderHeight(600);
                tempEntityList3.push_back(bossLevel1);
            }
            else if(spawnColor == ofColor::white) {
                int random = ofRandom(0, 1);
                if(random == 0) {
                    Structure* tree = new Structure("spruce", "images/entities/inmovable/tree_0.png", x, y, 1);
                    tree->getHitBox().setWidth(25);
                    tree->getHitBox().setHeight(170);
                    tree->getHitBox().setRenderWidth(80);
                    tree->getHitBox().setRenderHeight(170);
                    tempEntityList3.push_back(tree);
                }else {
                    Structure* tree = new Structure("oak", "images/entities/inmovable/tree_1.png", x, y, 1);
                    tree->getHitBox().setWidth(40);
                    tree->getHitBox().setHeight(170);
                    tree->getHitBox().setRenderWidth(170);
                    tree->getHitBox().setRenderHeight(170);
                    tempEntityList3.push_back(tree);
                }
            }
        }
    }

    ofPoint entrancePosition3(1679, 2003);

    Area* area1 = new Area("wild-life", cave, areaPath3, areaBoundryPath3, areaAudio3, areaFightingStage3, areaEffect3, entrancePosition3, tempEntityList3);
    generatedAreas.push_back(area1);


    //set this current area to last area (which is the first one)
    this->currentArea = area1;
}