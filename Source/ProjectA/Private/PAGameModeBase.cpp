// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "PAGameModeBase.h"
#include "Character/PACharacter.h"
#include "Player/PAPlayerController.h"

APAGameModeBase::APAGameModeBase()
{
	DefaultPawnClass = APACharacter::StaticClass();
	PlayerControllerClass = APAPlayerController::StaticClass();
}
