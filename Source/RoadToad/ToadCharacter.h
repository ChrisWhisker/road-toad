// Copyright © 2023-2024 Chris Worcester. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ToadCharacter.generated.h"

UCLASS()
class ROADTOAD_API AToadCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AToadCharacter();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ThisToadDistanceRecord;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
