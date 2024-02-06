#pragma once

#include "CoreMinimal.h"
#include "RoadToadDataTypes.generated.h"

// Possible reasons for toad death
UENUM(BlueprintType)
enum class ECauseOfDeath : uint8
{
	Car UMETA(DisplayName="Car"),
	Water UMETA(DisplayName="Water"),
	Timer UMETA(DisplayName="Timer"),
	Bird UMETA(DisplayName="Bird"),
};
