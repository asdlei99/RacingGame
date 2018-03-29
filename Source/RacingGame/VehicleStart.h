// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "VehicleStart.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API AVehicleStart : public APlayerStart
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class ACheckpoint*> Checkpoints;
};
