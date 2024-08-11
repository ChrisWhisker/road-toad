// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScoringSubsystem.generated.h"

class ARoadToadGameState;
class URoadToadHUD;

/**
 * 
 */
UCLASS()
class ROADTOAD_API UScoringSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPoints(int Points);

	UFUNCTION(BlueprintCallable)
	void UpdateHighScore(int NewHighScore);

	UFUNCTION(BlueprintCallable)
	void UpdateScoreMultiplier(int LevelNumber);

private:
	// New points added are multiplied by this number. Depends on the current level.
	UPROPERTY()
	float ScoreMultiplier = 1;

	UPROPERTY()
	TObjectPtr<ARoadToadGameState> RoadToadGameState;

	UPROPERTY()
	TObjectPtr<URoadToadHUD> RoadToadHUD;

	UFUNCTION()
	bool Setup();
};
