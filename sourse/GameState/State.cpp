#include "State.h"

#include "StateNewGame.h"
#include "StateSetting.h"
#include "StateAboutUs.h"
#include "StateMenu.h"
#include "StateModeGame.h"
#include "StateGuideGame.h"

State* State::CreateState(unsigned int state)
{
	State* gameState = nullptr;
	switch (state) {
	case 0:
		gameState = new StateMenu();
		break;
	case 1: // Mode Game
		gameState = new StateModeGame();
		break;
	case 2: // Setting
		gameState = new StateSetting();
		break;
	case 3:	// About us
		gameState = new StateAboutUs();
		break;
	case 4: // New Game
		gameState = new StateNewGame();
		break;
	case 5: // Guide Game
		gameState = new StateGuideGame();
	default:
		break;
	}
	return gameState;
}
