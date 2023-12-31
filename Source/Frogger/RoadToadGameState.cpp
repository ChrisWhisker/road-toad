// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "RoadToadGameState.h"

TArray<AActor*> ARoadToadGameState::AddToOccupiedHomes(AActor* EnteredHome)
{
	OccupiedHomes.Add(EnteredHome);
	return OccupiedHomes;
}

void ARoadToadGameState::EmptyOccupiedHomes()
{
	OccupiedHomes.Empty();
}

int ARoadToadGameState::TakeALife()
{
	return --LivesLeft;
}

int ARoadToadGameState::ResetLives()
{
	LivesLeft = MaxLives;
	return LivesLeft;
}

int ARoadToadGameState::AddPoints(const int NewPoints)
{
	return Score += NewPoints;
}

void ARoadToadGameState::ClearScore()
{
	Score = 0;
}

int ARoadToadGameState::IncrementLevel()
{
	return ++CurrentLevel;
}

void ARoadToadGameState::ResetToLevelOne()
{
	CurrentLevel = 1;
}
