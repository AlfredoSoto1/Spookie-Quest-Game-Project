#pragma once

#ifndef STATE_MASTER_HEADER
#define STATE_MASTER_HEADER

#include "State.h"
#include "TitleState.h"
#include "OverworldState.h"
#include "BattleState.h"
#include "WinState.h"
#include "EndGameState.h"

class StateMaster {
public:
    StateMaster(Player* player);
    virtual ~StateMaster();

    State& getCurrentState();

    void draw();
    void update();
private:
	Player *player;
    State *currentState;
    
	Area *currentArea;
    vector<Area*> generatedAreas;

	WinState *winState;
	TitleState *titleState;
	BattleState *battleState;
	EndGameState *endGameState;
	OverworldState *overworldState;

    void initAreas();
    void createStates();
};

#endif