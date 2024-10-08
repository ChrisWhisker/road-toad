// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "TimerSubsystem.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "RoadToad/RoadToadGameMode.h"
#include "RoadToad/RoadToadGameState.h"
#include "RoadToad/Widgets/RoadToadHUD.h"

bool UTimerSubsystem::Setup()
{
	// Get Game Mode
	if (!RoadToadGameMode)
	{
		const TObjectPtr<AGameModeBase> GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		if (!GameModeBase)
		{
			UE_LOG(LogTemp, Error, TEXT("No game mode found."));
			return false;
		}
		RoadToadGameMode = Cast<ARoadToadGameMode>(GameModeBase);
		if (!RoadToadGameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("Game mode found is not of type ARoadToadGameMode."));
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

void UTimerSubsystem::RestartLifeTimer()
{
	if (!Setup())
	{
		UE_LOG(LogTemp, Error, TEXT("Setup failed."));
		return;
	}

	LifeTimerSecondsLeft = LifeTimerMaxSeconds;
	RoadToadHUD->UpdateLifeTimer(1);
	LifeTimerTicking = true;

	// Start the timer
	float Interval = 0.1;
	FTimerDelegate TimerCallback;
	TimerCallback.BindUObject(this, &UTimerSubsystem::TickLifeTimer, Interval);
	GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, TimerCallback, Interval, true);
}

void UTimerSubsystem::PauseLifeTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(LifeTimerHandle);
	LifeTimerTicking = false;
}

void UTimerSubsystem::TickLifeTimer(const float SecondsPassed)
{
	if (!LifeTimerTicking)
	{
		UE_LOG(LogTemp, Warning, TEXT("Life timer tried to tick but it's disabled."));
		return;
	}

	if (!Setup())
	{
		UE_LOG(LogTemp, Error, TEXT("Setup failed."));
		return;
	}

	LifeTimerSecondsLeft -= SecondsPassed;
	RoadToadHUD->UpdateLifeTimer(LifeTimerSecondsLeft / LifeTimerMaxSeconds);
	if (LifeTimerSecondsLeft <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(LifeTimerHandle);
		RoadToadGameMode->KillToad(ECauseOfDeath::Timer);
	}
}

void UTimerSubsystem::RestartJumpTimer()
{
	if (!Setup())
	{
		UE_LOG(LogTemp, Error, TEXT("Setup failed."));
		return;
	}

	RoadToadGameMode->ToadCanJump = false;
	JumpTimerSeconds = 0;
	RoadToadHUD->UpdateJumpTimer(JumpTimerSeconds);
	JumpTimerTicking = true;

	// Start the timer
	float Interval = 0.1;
	FTimerDelegate TimerCallback;
	TimerCallback.BindUObject(this, &UTimerSubsystem::TickJumpTimer, Interval);
	GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, TimerCallback, Interval, true);
}

void UTimerSubsystem::TickJumpTimer(const float SecondsPassed)
{
	if (!JumpTimerTicking)
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump timer tried to tick but it's disabled."));
		return;
	}

	if (!Setup())
	{
		UE_LOG(LogTemp, Error, TEXT("Setup failed."));
		return;
	}

	JumpTimerSeconds += SecondsPassed;
	const float TimerProgress = JumpTimerSeconds / JumpTimerMaxSeconds;
	RoadToadHUD->UpdateJumpTimer(TimerProgress);
	if (TimerProgress >= 1)
	{
		RoadToadGameMode->ToadCanJump = true;
		GetWorld()->GetTimerManager().ClearTimer(JumpTimerHandle);
	}
}
