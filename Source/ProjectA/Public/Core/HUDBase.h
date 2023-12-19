// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDBase.generated.h"


UCLASS()
class PROJECTA_API AHUDBase : public AHUD
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	
	void CreateHUDWidget();
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	
};
