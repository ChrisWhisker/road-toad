// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "Car.h"

ACar::ACar()
{
	RespawnDistance = 800;
}

void ACar::Respawn_Implementation()
{
	Super::Respawn();
}

void ACar::SpawnPowerUp_Implementation(const bool Bubble)
{
	Super::SpawnPowerUp(Bubble);
}

void ACar::DespawnPowerUps_Implementation()
{
	Super::DespawnPowerUps();
}
