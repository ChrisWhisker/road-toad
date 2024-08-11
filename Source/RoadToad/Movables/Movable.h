// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Movable.generated.h"

class UPowerUp;
class ARoadToadGameMode;

UCLASS()
class ROADTOAD_API AMovable : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovable();

	// Speed at levels > 1 is determined by this number and the level number
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BaseSpeed;

	// Current speed
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	virtual void SpawnPowerUp(bool Bubble);

	virtual void DespawnPowerUps();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Enabled = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Slowed = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Moving = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RespawnDistance = 100;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ARoadToadGameMode> RoadToadGameMode;

	virtual void Respawn();

public:	
	virtual void Tick(float DeltaTime) override;
};
