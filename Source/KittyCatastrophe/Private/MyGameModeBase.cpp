// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "MyGameModeBase.h"
#include "MyGameStateBase.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"


AMyGameModeBase::AMyGameModeBase()
{
	GameStateClass        = AMyGameStateBase::StaticClass();
	PlayerStateClass      = AMyPlayerState::StaticClass();
    PlayerControllerClass = AMyPlayerController::StaticClass();
}
