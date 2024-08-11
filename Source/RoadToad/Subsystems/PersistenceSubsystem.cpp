// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#include "PersistenceSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UPersistenceSubsystem::Save()
{
	if (!DataIsDirty)
	{
		UE_LOG(LogTemp, Warning, TEXT("Save data is not marked dirty. Not saving."));
		return;
	}

	if (!SaveData)
	{
		const TObjectPtr<USaveGame> NewSaveGame = UGameplayStatics::CreateSaveGameObject(URoadToadSaveGame::StaticClass());
		SaveData = Cast<URoadToadSaveGame>(NewSaveGame);
	}

	// Set up the (optional) delegate.
	FAsyncSaveGameToSlotDelegate SavedDelegate;
	// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
	SavedDelegate.BindUObject(this, &UPersistenceSubsystem::OnSave);

	// Set data on the savegame object.
	//SaveGameInstance->PlayerName = TEXT("PlayerOne");

	// Start async save process.
	UGameplayStatics::AsyncSaveGameToSlot(SaveData, SLOT_NAME, 0, SavedDelegate);
}

void UPersistenceSubsystem::Load()
{
	// Set up the delegate.
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	LoadedDelegate.BindUObject(this, &UPersistenceSubsystem::OnLoad);
	UGameplayStatics::AsyncLoadGameFromSlot(SLOT_NAME, 0, LoadedDelegate);
}

void UPersistenceSubsystem::SetSoundsVolume(const float NewVolume)
{
	if (!SaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't save without existing save data. Make sure you load before saving."));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Saving sounds volume as %f."), NewVolume);
	SaveData->SoundsVolume = NewVolume;
	DataIsDirty = true;
	Save();
}

void UPersistenceSubsystem::SetMusicVolume(const float NewVolume)
{
	if (!SaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't save without existing save data. Make sure you load before saving."));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Saving music volume as %f."), NewVolume);
	SaveData->MusicVolume = NewVolume;
	DataIsDirty = true;
	Save();
}

void UPersistenceSubsystem::SetHighScore(const int NewHighScore)
{
	if (!SaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't save without existing save data. Make sure you load before saving."));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Saving high score as %i."), NewHighScore);
	SaveData->HighScore = NewHighScore;
	DataIsDirty = true;
	Save();
}

void UPersistenceSubsystem::SetHighestLevelReached(const int NewLevel)
{
	if (!SaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't save without existing save data. Make sure you load before saving."));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Saving highest level reached as %i."), NewLevel);
	SaveData->HighestLevelReached = NewLevel;
	DataIsDirty = true;
	Save();
}

void UPersistenceSubsystem::OnSave(const FString& SlotName, const int32 UserIndex, const bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("Data successfully saved."));
		DataIsDirty = false;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Data failed to save."));
	}
}

void UPersistenceSubsystem::OnLoad(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	if (!LoadedGameData)
	{
		UE_LOG(LogTemp, Log, TEXT("No save data found. Creating new save data."));
		const TObjectPtr<USaveGame> NewSaveGame = UGameplayStatics::CreateSaveGameObject(
			URoadToadSaveGame::StaticClass());
		SaveData = Cast<URoadToadSaveGame>(NewSaveGame);
		DataLoaded.Broadcast(SaveData);
		return;
	}

	const TObjectPtr<URoadToadSaveGame> NewSaveData = Cast<URoadToadSaveGame>(LoadedGameData);
	if (!NewSaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("Loaded data is not the correct type."));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Data successfully loaded."));
	SaveData = NewSaveData;
	DataLoaded.Broadcast(SaveData);
}
