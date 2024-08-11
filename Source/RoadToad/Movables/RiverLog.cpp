// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "RiverLog.h"

ARiverLog::ARiverLog()
{
	RespawnDistance = 900;
}

void ARiverLog::Respawn_Implementation()
{
	Super::Respawn();
}

void ARiverLog::SpawnPowerUp_Implementation(const bool Bubble)
{
	Super::SpawnPowerUp(Bubble);
}

void ARiverLog::DespawnPowerUps_Implementation()
{
	Super::DespawnPowerUps();
}
