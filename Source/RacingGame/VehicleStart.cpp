// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleStart.h"
#include "VehiclePlayerController.h"

void AVehicleStart::BeginPlay()
{
	Super::BeginPlay();

	Cast<AVehiclePlayerController>(GetWorld()->GetFirstPlayerController())->Checkpoints = Checkpoints;
	Cast<AVehiclePlayerController>(GetWorld()->GetFirstPlayerController())->TotalCheckpoints = Checkpoints.Num();
}