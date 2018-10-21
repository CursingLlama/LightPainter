// Fill out your copyright notice in the Description page of Project Settings.

#include "PaletteMenuHandController.h"

#include "Components/WidgetComponent.h"

APaletteMenuHandController::APaletteMenuHandController()
{
	PrimaryActorTick.bCanEverTick = false;

	PaletteMenu = CreateDefaultSubobject<UWidgetComponent>(FName("Palette Menu"));
	PaletteMenu->SetupAttachment(GetRootComponent());
}

// Called every frame
void APaletteMenuHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
