// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "RoadToadGameState.h"

TArray<AActor*> ARoadToadGameState::AddToOccupiedHomes(TSoftObjectPtr<AActor> EnteredHome)
{
	OccupiedHomes.Add(EnteredHome.Get());
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
	Score += NewPoints;
	if (Score > HighScore)
	{
		HighScore = Score;
	}
	return Score;
}

void ARoadToadGameState::ClearScore()
{
	Score = 0;
}

int ARoadToadGameState::IncrementLevel()
{
	return ++CurrentLevel;
}

int ARoadToadGameState::SetLevel(const int NewLevel)
{
	CurrentLevel = NewLevel;
	return CurrentLevel;
}

void ARoadToadGameState::ResetToLevelOne()
{
	CurrentLevel = 1;
}
