// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "ToadCharacter.h"

AToadCharacter::AToadCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AToadCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AToadCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AToadCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
