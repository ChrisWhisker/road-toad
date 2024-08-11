// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PowerUpSubsystem.generated.h"

class AToadCharacter;
class AAmbientSound;
class ACar;
class AMovable;
class ARiverLog;
class ATurtleChain;

/**
 * 
 */
UCLASS()
class ROADTOAD_API UPowerUpSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void TriggerSpawnPowerUp();

	UFUNCTION(BlueprintCallable)
	void ToggleNightMode();

	UFUNCTION(BlueprintCallable)
	void DespawnPowerUps();

private:
	UPROPERTY()
	TObjectPtr<AToadCharacter> ToadCharacter;

	UPROPERTY()
	FTimerHandle SpawnPowerUpTimerHandle;

	// Chance to spawn a bubble vs. slow power-up (0 = always spawn slow, 1 = always spawn bubble)
	UPROPERTY()
	float PowerUpBubbleChance = 0.5;

	UPROPERTY()
	bool NightMode = false;

	UPROPERTY()
	bool NightModeBeforeSlow = false;

	// TODO Comment out any of these arrays that are never used
	// {
	UPROPERTY()
	TArray<AMovable*> Movables;

	UPROPERTY()
	TArray<ACar*> Cars;

	UPROPERTY()
	TArray<ARiverLog*> Logs;

	UPROPERTY()
	TArray<ATurtleChain*> TurtleChains;
	// }

	UPROPERTY()
	float MovableSlowFactor = 4;

	UFUNCTION()
	bool Setup();

	UFUNCTION()
	void SpawnPowerUp();

	UFUNCTION()
	void SlowMovables();

	UFUNCTION()
	void ResetMovablesSpeed();

	UFUNCTION()
	void SwitchToDay();

	UFUNCTION()
	void SwitchToNight();
};
