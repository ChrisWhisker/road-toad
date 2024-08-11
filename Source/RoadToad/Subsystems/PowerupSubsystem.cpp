// Copyright © 2023-2024 Chris Worcester. All rights reserved.


#include "PowerUpSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "RoadToad/ToadCharacter.h"
#include "RoadToad/Movables/Car.h"
#include "RoadToad/Movables/Movable.h"
#include "RoadToad/Movables/RiverLog.h"
#include "RoadToad/Movables/TurtleChain.h"

bool UPowerUpSubsystem::Setup()
{
	if (!ToadCharacter)
	{
		const TObjectPtr<APawn> Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (!Pawn)
		{
			UE_LOG(LogTemp, Error, TEXT("Player pawn not found."));
			return false;
		}
		ToadCharacter = Cast<AToadCharacter>(Pawn);
	}

	if (Movables.IsEmpty() || Cars.IsEmpty() || Logs.IsEmpty() || TurtleChains.IsEmpty())
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMovable::StaticClass(), FoundActors);
		if (FoundActors.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("No movables found."));
			return false;
		}

		for (TObjectPtr<AActor> Movable : FoundActors)
		{
			Movables.Add(Cast<AMovable>(Movable));

			if (Movable->IsA(ACar::StaticClass()))
			{
				Cars.Add(Cast<ACar>(Movable));
			}
			else if (Movable->IsA(ARiverLog::StaticClass()))
			{
				Logs.Add(Cast<ARiverLog>(Movable));
			}
			else if (Movable->IsA(ATurtleChain::StaticClass()))
			{
				TurtleChains.Add(Cast<ATurtleChain>(Movable));
			}
		}
	}

	return true;
}

void UPowerUpSubsystem::TriggerSpawnPowerUp()
{
	DespawnPowerUps();
	const float Delay = FMath::FRandRange(2.0, 6.0);
	UE_LOG(LogTemp, Log, TEXT("Spawning powerup in %f seconds"), Delay);
	FTimerDelegate TimerCallback;
	TimerCallback.BindUObject(this, &UPowerUpSubsystem::SpawnPowerUp);
	GetWorld()->GetTimerManager().SetTimer(SpawnPowerUpTimerHandle, TimerCallback, Delay, false);
}

void UPowerUpSubsystem::SpawnPowerUp()
{
	if (!Setup())
	{
		return;
	}
	DespawnPowerUps();

	UE_LOG(LogTemp, Log, TEXT("Spawning power-up"));

	// Pick a random movable to spawn a power-up on
	TObjectPtr<AMovable> SelectedMovable;
	if (ToadCharacter->ThisToadDistanceRecord >= 500) // If toad has crossed the road
	{
		if (FMath::RandBool())
		{
			SelectedMovable = TurtleChains[FMath::RandRange(0, TurtleChains.Num() - 1)];
			UE_LOG(LogTemp, Log, TEXT("Turtle chain selected."));
		}
		else
		{
			SelectedMovable = Logs[FMath::RandRange(0, Logs.Num() - 1)];
			UE_LOG(LogTemp, Log, TEXT("Log selected."));
		}
	}
	else
	{
		SelectedMovable = Cars[FMath::RandRange(0, Cars.Num() - 1)];
	}

	// Choose to spawn a bubble or a slow power-up
	const bool SpawnBubble = UKismetMathLibrary::RandomBoolWithWeight(PowerUpBubbleChance);
	PowerUpBubbleChance = SpawnBubble ? PowerUpBubbleChance - 0.5 : PowerUpBubbleChance + 0.5;

	SelectedMovable->SpawnPowerUp(SpawnBubble);
}

void UPowerUpSubsystem::SlowMovables()
{
}

void UPowerUpSubsystem::ResetMovablesSpeed()
{
}

void UPowerUpSubsystem::ToggleNightMode()
{
}

void UPowerUpSubsystem::DespawnPowerUps()
{
	if (!Setup())
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("De-spawning all powerups."));
	GetWorld()->GetTimerManager().ClearTimer(SpawnPowerUpTimerHandle);

	for (AMovable* Movable : Movables)
	{
		Movable->DespawnPowerUps();
	}
}

void UPowerUpSubsystem::SwitchToDay()
{
}

void UPowerUpSubsystem::SwitchToNight()
{
}
