// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "ToadCharacter.h"

// Sets default values
AToadCharacter::AToadCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AToadCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToadCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AToadCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

