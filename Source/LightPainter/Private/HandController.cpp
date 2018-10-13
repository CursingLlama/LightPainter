// Fill out your copyright notice in the Description page of Project Settings.

#include "HandController.h"
#include "Stroke.h"

#include "Engine/World.h"
#include "MotionControllerComponent.h"

// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetShowDeviceModel(true);
}

// Called when the game starts or when spawned
void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStroke)
	{
		FVector Cursor = GetActorLocation() + GetActorForwardVector() * 5;
		CurrentStroke->Update(Cursor);
	}
}

void AHandController::SetHand(FName Hand)
{
	MotionController->SetTrackingMotionSource(Hand);
}

void AHandController::TriggerPressed()
{
	if (!StrokeClass) return;

	FVector Cursor = GetActorLocation() + GetActorForwardVector() * 5;
	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass, Cursor, FRotator(0));
}

void AHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
}

