// Fill out your copyright notice in the Description page of Project Settings.

#include "UIPointerHandController.h"

#include "Components/WidgetInteractionComponent.h"
#include "InputCoreTypes.h"


AUIPointerHandController::AUIPointerHandController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	LaserPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(FName("Laser Pointer"));
	LaserPointer->SetupAttachment(GetRootComponent());
	LaserPointer->bShowDebug = true;
	LaserPointer->DebugColor = FLinearColor(0.9f, 0, 0);
}

// Called every frame
void AUIPointerHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AUIPointerHandController::TriggerPressed()
{
	LaserPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::TriggerReleased()
{
	LaserPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}
