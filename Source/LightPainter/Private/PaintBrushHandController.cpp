// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintBrushHandController.h"
#include "Stroke.h"

#include "Engine/World.h"

// Sets default values
APaintBrushHandController::APaintBrushHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStroke)
	{
		FVector Cursor = GetActorLocation() + GetActorForwardVector() * 5;
		CurrentStroke->Update(Cursor);
	}
}

void APaintBrushHandController::TriggerPressed()
{
	if (!StrokeClass) return;

	FVector Cursor = GetActorLocation() + GetActorForwardVector() * 5;
	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass, Cursor, FRotator(0));
}

void APaintBrushHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
}

