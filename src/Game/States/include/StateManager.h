#pragma once

#ifndef STATE_MANAGER_HEADER
#define STATE_MANAGER_HEADER

#include "State.h"
#include "TitleState.h"
#include "OverworldState.h"
#include "BattleState.h"
#include "WinState.h"
#include "EndGameState.h"

class StateManager {
public:
    StateManager(Player* player);
    virtual ~StateManager();

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