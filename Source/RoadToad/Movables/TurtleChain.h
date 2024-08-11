// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Movable.h"
#include "TurtleChain.generated.h"

/**
 * 
 */
UCLASS()
class ROADTOAD_API ATurtleChain : public AMovable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurtleChain();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnPowerUp(bool Bubble) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DespawnPowerUps() override;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Respawn() override;
};
