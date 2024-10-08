// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#include "AudioSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"

void UAudioSubsystem::PlaySound(USoundBase* Sound, const float Pitch) const
{
	if (!Sound)
	{
		UE_LOG(LogTemp, Error, TEXT("No sound provided. Nothing to play."));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Playing sound: %s."), *Sound->GetName());
	UGameplayStatics::PlaySound2D(this, Sound, SoundsVolume, Pitch);
}

void UAudioSubsystem::MuteMusic()
{
	UE_LOG(LogTemp, Log, TEXT("Muting music."));
	MusicVolumeIfOn = MusicVolume;
	MusicVolume = 0;
	UpdateMusicComponentVolume();
	// TODO PersistenceSubsystem->SetMusicVolume(0);
}

void UAudioSubsystem::UnmuteMusic()
{
	UE_LOG(LogTemp, Log, TEXT("Unmuting music."));
	MusicVolume = MusicVolumeIfOn;
	UpdateMusicComponentVolume();
	// TODO PersistenceSubsystem->SetMusicVolume(MusicVolumeIfOn);
}

bool UAudioSubsystem::ToggleMusic()
{
	UE_LOG(LogTemp, Log, TEXT("Toggling music."));
	if (GetMusicOn())
	{
		MuteMusic();
		return false;
	}

	UnmuteMusic();
	return true;
}

bool UAudioSubsystem::SetMusicVolume(const float NewVolume)
{
	UE_LOG(LogTemp, Log, TEXT("Setting music volume to %f."), NewVolume);
	MusicVolume = NewVolume;
	UpdateMusicComponentVolume();
	return GetMusicOn();
}

void UAudioSubsystem::UpdateMusicComponentVolume()
{
	UE_LOG(LogTemp, Log, TEXT("Updating music component volume."));

	if (!GetMusicActor())
	{
		UE_LOG(LogTemp, Error, TEXT("No music actor found. Can't update music volume."));
		return;
	}

	GetMusicActor()->GetAudioComponent()->SetVolumeMultiplier(MusicVolume * BASE_MUSIC_VOLUME_MULTIPLIER);
}

void UAudioSubsystem::MuteSounds()
{
	UE_LOG(LogTemp, Log, TEXT("Muting sounds."));
	SoundsVolumeIfOn = SoundsVolume;
	SoundsVolume = 0;
	// TODO PersistenceSubsystem->SetSoundsVolume(0);
}

void UAudioSubsystem::UnmuteSounds()
{
	UE_LOG(LogTemp, Log, TEXT("Unmuting sounds."));
	SoundsVolume = SoundsVolumeIfOn;
	// TODO PersistenceSubsystem->SetSoundsVolume(SoundsVolumeIfOn);
}

bool UAudioSubsystem::ToggleSounds()
{
	UE_LOG(LogTemp, Log, TEXT("Toggling sounds."));
	if (GetSoundsOn())
	{
		MuteSounds();
		return false;
	}

	UnmuteSounds();
	return true;
}

bool UAudioSubsystem::SetSoundsVolume(const float NewVolume)
{
	UE_LOG(LogTemp, Log, TEXT("Setting sounds volume to %f."), NewVolume);
	SoundsVolume = NewVolume;
	return GetSoundsOn();
}

TSoftObjectPtr<AAmbientSound> UAudioSubsystem::GetMusicActor()
{
	UE_LOG(LogTemp, Log, TEXT("Getting music actor."));
	if (!MusicActor.IsSet())
	{
		const TObjectPtr<AActor> MusicActorNative = UGameplayStatics::GetActorOfClass(GetWorld(), AAmbientSound::StaticClass());
		if (!MusicActorNative)
		{
			UE_LOG(LogTemp, Error, TEXT("Music actor could not be found."));
			return nullptr;
		}
		UE_LOG(LogTemp, Log, TEXT("Music actor found."));
		MusicActor = Cast<AAmbientSound>(MusicActorNative);
	}
	return MusicActor.GetValue();
}
