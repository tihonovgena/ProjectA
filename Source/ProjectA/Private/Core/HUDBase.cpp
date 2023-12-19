// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Core/HUDBase.h"
#include "Blueprint/UserWidget.h"

void AHUDBase::BeginPlay()
{
	Super::BeginPlay();
	
	CreateHUDWidget();
	
}

void AHUDBase::CreateHUDWidget()
{
	if (HUDWidgetClass)
	{
		UUserWidget* HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		HUDWidget->AddToViewport();
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUD widget class is empty"));
		checkNoEntry()
	}
}
