// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Dev/DevRadialDamage.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADevRadialDamage::ADevRadialDamage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    if (Scene)
    {
    	RootComponent = Scene;
    }
	

}

// Called when the game starts or when spawned
void ADevRadialDamage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADevRadialDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(),GetActorLocation(),SphereRadius,20, SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), TickDamage, GetActorLocation(), SphereRadius, nullptr, {}, this, nullptr, bDoFullDamage);
}

