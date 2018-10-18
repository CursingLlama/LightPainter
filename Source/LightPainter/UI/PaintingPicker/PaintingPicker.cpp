// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingPicker.h"
#include "PaintingGrid.h"

#include "Components/WidgetComponent.h"


// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(FName("PaintingGrid"));
	PaintingGrid->SetupAttachment(Root);

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(FName("ActionBar"));
	ActionBar->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();
	UPaintingGrid* UserWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (UserWidget)
	{
		UserWidget->AddPainting();
	}
}

// Called every frame
void APaintingPicker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

