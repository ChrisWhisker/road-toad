// Copyright © 2023 Chris Worcester. All rights reserved.

#pragma once

#include "Misc/Optional.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioSubsystem.generated.h"

class AAmbientSound;

/**
 *
 */
UCLASS()
class FROGGER_API UAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* Sound, float Pitch = 1) const;

	UFUNCTION(BlueprintCallable)
	void MuteMusic();

	UFUNCTION(BlueprintCallable)
	void UnmuteMusic();

	UFUNCTION(BlueprintCallable)
	bool ToggleMusic();

	UFUNCTION(BlueprintCallable)
	bool SetMusicVolume(const float NewVolume);

	UFUNCTION(BlueprintCallable)
	void MuteSounds();

	UFUNCTION(BlueprintCallable)
	void UnmuteSounds();

	UFUNCTION(BlueprintCallable)
	bool ToggleSounds();

	/**
	 * @brief
	 * @param NewVolume
	 * @return whether or not sounds are on
	 */
	UFUNCTION(BlueprintCallable)
	bool SetSoundsVolume(const float NewVolume);

	UFUNCTION(BlueprintCallable)
	bool GetMusicOn() const { return MusicVolume > 0; };

	UFUNCTION(BlueprintCallable)
	bool GetSoundsOn() const { return SoundsVolume > 0; };

	UFUNCTION(BlueprintCallable)
	float GetMusicVolume() const { return MusicVolume; };

	UFUNCTION(BlueprintCallable)
	float GetSoundsVolume() const { return SoundsVolume; };

private:
	UFUNCTION()
	AAmbientSound* GetMusicActor();

	TOptional<AAmbientSound*> MusicActor;

	/* Defines the maximum music volume. 1 = same volume as sounds. */
	const float BASE_MUSIC_VOLUME_MULTIPLIER = 0.5f;

	UFUNCTION()
	void UpdateMusicComponentVolume();

	UPROPERTY()
	float MusicVolume = 1.0f;

	UPROPERTY()
	float MusicVolumeIfOn = 1.0f;

	UPROPERTY()
	float SoundsVolume = 1.0f;

	UPROPERTY()
	float SoundsVolumeIfOn = 1.0f;
};
