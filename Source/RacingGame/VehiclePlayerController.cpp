// Fill out your copyright notice in the Description page of Project Settings.

#include "VehiclePlayerController.h"
#include "Checkpoint.h"

void AVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		Widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);
		if (Widget)
			Widget->AddToViewport();
	}

	SaveGameCheck();
}

void AVehiclePlayerController::StartGameSetup()
{
	for (int i = 0; i < TotalCheckpoints; i++)
	{
		Checkpoints[i]->CheckpointNumber = i;
		Checkpoints[i]->ShouldOverlap = false;
	}

	ActivateCheckpoint(Checkpoints[0]);

	StartRaceTime();
}

void AVehiclePlayerController::ActivateCheckpoint(ACheckpoint * Checkpoint)
{
	Checkpoint->ShouldOverlap = true;
}

void AVehiclePlayerController::OnCheckpointCleared(int Checkpoint)
{
	if (Checkpoint + 1 == TotalCheckpoints)
	{
		IsRacing = false;
		StopRaceTime();
		RaceTimeCheck();
		ShowMenu();
	}
	else
		ActivateCheckpoint(Checkpoints[Checkpoint + 1]);
}

void AVehiclePlayerController::RaceTimeCheck()
{
	if (RaceTime <= WorstRaceTime)
		SaveGame();
}

FText AVehiclePlayerController::TimeToText(float Time)
{
	FString Minutes = (FMath::FloorToInt(FMath::FloorToInt(Time / 60.0f)) > 9) ? FString::FromInt(FMath::FloorToInt(Time / 60.0f)) : ("0" + FString::FromInt(FMath::FloorToInt(Time / 60.0f)));
	FString Seconds = (FMath::FloorToInt(FMath::FloorToInt(FMath::Fmod(Time, 60.0f))) > 9) ? FString::FromInt(FMath::FloorToInt(FMath::Fmod(Time, 60.0f))) : ("0" + FString::FromInt(FMath::FloorToInt(FMath::Fmod(Time, 60.0f))));
	FString Milliseconds = (FMath::FloorToInt((Time - FMath::FloorToInt(Time)) * 100) > 9) ? FString::FromInt(FMath::FloorToInt((Time - FMath::FloorToInt(Time)) * 100)) : ("0" + FString::FromInt(FMath::FloorToInt((Time - FMath::FloorToInt(Time)) * 100)));
		
	return FText::FromString(Minutes + ":" + Seconds + "." + Milliseconds);
}
