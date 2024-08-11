// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "TurtleChain.h"

ATurtleChain::ATurtleChain()
{
	RespawnDistance = 900;
}

void ATurtleChain::Respawn_Implementation()
{
	Super::Respawn();
}

void ATurtleChain::SpawnPowerUp_Implementation(const bool Bubble)
{
	Super::SpawnPowerUp(Bubble);
}

void ATurtleChain::DespawnPowerUps_Implementation()
{
	Super::DespawnPowerUps();
}
