// Copyright © 2023 Chris Worcester. All rights reserved.

#include "AudioSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"

void UAudioSubsystem::PlaySound(USoundBase* Sound, const float Pitch) const
{
	UE_LOG(LogTemp, Log, TEXT("Playing sound."));
	UGameplayStatics::PlaySound2D(this, Sound, SoundsVolume, Pitch);
}

void UAudioSubsystem::MuteMusic()
{
	UE_LOG(LogTemp, Log, TEXT("Muting music."));
	MusicVolumeIfOn = MusicVolume;
	MusicVolume = 0;
	UpdateMusicComponentVolume();
}

void UAudioSubsystem::UnmuteMusic()
{
	UE_LOG(LogTemp, Log, TEXT("Unmuting music."));
	MusicVolume = MusicVolumeIfOn;
	UpdateMusicComponentVolume();
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
	GetMusicActor()->GetAudioComponent()->SetVolumeMultiplier(MusicVolume * BASE_MUSIC_VOLUME_MULTIPLIER);
}

void UAudioSubsystem::MuteSounds()
{
	UE_LOG(LogTemp, Log, TEXT("Muting sounds."));
	SoundsVolumeIfOn = SoundsVolume;
	SoundsVolume = 0;
}

void UAudioSubsystem::UnmuteSounds()
{
	UE_LOG(LogTemp, Log, TEXT("Unmuting sounds."));
	SoundsVolume = SoundsVolumeIfOn;
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

AAmbientSound* UAudioSubsystem::GetMusicActor()
{
	UE_LOG(LogTemp, Log, TEXT("Getting music actor."));
	if (!MusicActor.IsSet())
	{
		AActor* MusicActorNative = UGameplayStatics::GetActorOfClass(GetWorld(), AAmbientSound::StaticClass());
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
