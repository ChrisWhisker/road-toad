// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Movable.h"
#include "RiverLog.generated.h"

/**
 * 
 */
UCLASS()
class ROADTOAD_API ARiverLog : public AMovable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARiverLog();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	// ReSharper disable once CppEnforceOverridingFunctionStyle
	void SpawnPowerUp(bool Bubble) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	// ReSharper disable once CppEnforceOverridingFunctionStyle
	void DespawnPowerUps() override;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	// ReSharper disable once CppEnforceOverridingFunctionStyle
	void Respawn() override;
};
