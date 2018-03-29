// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UserWidget.h"
#include "VehiclePlayerController.generated.h"

/**
 * 
 */

class ACheckpoint;
 
UCLASS()
class RACINGGAME_API AVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ActivateCheckpoint(ACheckpoint* Checkpoint);
	void RaceTimeCheck();

	UFUNCTION(BlueprintPure, BlueprintCallable)
		FText TimeToText(float Time);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StartRaceTime();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StopRaceTime();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SaveGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LoadGame();

	UFUNCTION(BlueprintImplementableEvent)
		void SaveGameCheck();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowMenu();

	UFUNCTION(BlueprintCallable)
		void StartGameSetup();

	UFUNCTION(BlueprintCallable)
		void OnCheckpointCleared(int Checkpoint);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UUserWidget* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RaceTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WorstRaceTime = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText RaceTimeText = FText::FromString("00:00.00");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ACheckpoint*> Checkpoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int TotalCheckpoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsRacing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText PlayerName = FText::FromString("Unknown");
};
