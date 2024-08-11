// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "RoadToad/RoadToadSaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PersistenceSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataLoaded, URoadToadSaveGame*, NewSaveData);

// Manages saving and loading game data
UCLASS()
class ROADTOAD_API UPersistenceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// ****************************** Persistence ******************************

	// Try to save the game data
	UFUNCTION(BlueprintCallable)
	void Save();

	// Try to load the game data
	UFUNCTION(BlueprintCallable)
	void Load();

	// ****************************** Set values ******************************

	// Set the sounds volume and save the game data
	UFUNCTION(BlueprintCallable)
	void SetSoundsVolume(float NewVolume);

	// Set the music volume and save the game data
	UFUNCTION(BlueprintCallable)
	void SetMusicVolume(float NewVolume);

	// Set the high score and save the game data
	UFUNCTION(BlueprintCallable)
	void SetHighScore(int NewHighScore);

	// Set the high score and save the game data
	UFUNCTION(BlueprintCallable)
	void SetHighestLevelReached(int NewLevel);

	// ****************************** Delegates ******************************

	// Delegate called when the game data is saved or fails to save
	UFUNCTION()
	void OnSave(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	// Delegate called when the game data is loaded
	UFUNCTION()
	void OnLoad(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	// Call when the player can press a key to try the current level again
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnDataLoaded DataLoaded;

	// ****************************** Helpers ******************************

	// Get the currently loaded SaveGame data object
	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<URoadToadSaveGame> GetSaveData() const { return SaveData; };

private:
	// Contains all data to be saved and loaded
	UPROPERTY(BlueprintType)
	TObjectPtr<URoadToadSaveGame> SaveData;

	// True if data has changed since saving
	UPROPERTY()
	bool DataIsDirty = false;

	UPROPERTY()
	// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
	FString SLOT_NAME = "Default Slot";
};
