// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "ScoringSubsystem.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "RoadToad/RoadToadGameState.h"
#include "RoadToad/Widgets/RoadToadHUD.h"

bool UScoringSubsystem::Setup()
{
	// Get Game State
	if (!RoadToadGameState)
	{
		const TObjectPtr<AGameStateBase> GameStateBase = GetWorld()->GetGameState();
		if (!GameStateBase)
		{
			UE_LOG(LogTemp, Error, TEXT("No game state found."));
			return false;
		}
		RoadToadGameState = Cast<ARoadToadGameState>(GameStateBase);
		if (!RoadToadGameState)
		{
			UE_LOG(LogTemp, Error, TEXT("Game state found is not of type ARoadToadGameState."));
			return false;
		}
	}

	// Get HUD widget
	if (!RoadToadHUD)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, URoadToadHUD::StaticClass(), false);
		if (FoundWidgets.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("Road Toad HUD was not found."));
			return false;
		}
		RoadToadHUD = Cast<URoadToadHUD>(FoundWidgets[0]);
	}

	// Setup succeeded
	return true;
}

void UScoringSubsystem::AddPoints(const int Points)
{
	if (!Setup())
	{
		UE_LOG(LogTemp, Error, TEXT("Setup failed."));
		return;
	}

	const int NewScore = RoadToadGameState->AddPoints(Points * ScoreMultiplier);
	RoadToadHUD->UpdateScore(NewScore);
	RoadToadHUD->UpdateHighScore(RoadToadGameState->HighScore);
}

void UScoringSubsystem::UpdateHighScore(const int NewHighScore)
{
	if (!Setup())
	{
		UE_LOG(LogTemp, Error, TEXT("Setup failed."));
		return;
	}

	RoadToadGameState->HighScore = NewHighScore;
	RoadToadHUD->UpdateHighScore(NewHighScore);
}

void UScoringSubsystem::UpdateScoreMultiplier(const int LevelNumber)
{
	ScoreMultiplier = (static_cast<float>(LevelNumber) / 2.0) + 0.5;
	UE_LOG(LogTemp, Log, TEXT("New score multiplier is %f"), ScoreMultiplier);
}
