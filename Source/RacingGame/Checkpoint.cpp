// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"
#include "VehiclePlayerController.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	ArrowComponent = this->CreateDefaultSubobject<UArrowComponent>("Arrow");
	ArrowComponent->SetupAttachment(RootComponent);

	Trigger = this->CreateAbstractDefaultSubobject<UBoxComponent>("Trigger");
	Trigger->SetBoxExtent(FVector(32.0f, 1000.0f, 256.0f), true);
	Trigger->SetCollisionProfileName("OverlapOnlyPawn");
	Trigger->bGenerateOverlapEvents = true;
	ShouldOverlap = true;
	Trigger->SetupAttachment(RootComponent);
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnTriggerEndOverlap);
}

void ACheckpoint::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((FVector::DotProduct(OtherActor->GetVelocity(), ArrowComponent->GetForwardVector()) > 0.0f) && ShouldOverlap)
	{
		Cast<AVehiclePlayerController>(GetWorld()->GetFirstPlayerController())->OnCheckpointCleared(CheckpointNumber);
		ShouldOverlap = false;
	}
}