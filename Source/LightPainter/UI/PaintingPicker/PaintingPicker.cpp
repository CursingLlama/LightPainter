// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingPicker.h"
#include "PaintingGrid.h"
#include "Saving/PainterSaveGame.h"
#include "Saving/PainterSaveGameIndex.h"

#include "Components/WidgetComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"


// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(FName("PaintingGrid"));
	PaintingGrid->SetupAttachment(Root);

	//ActionBar = CreateDefaultSubobject<UWidgetComponent>(FName("ActionBar"));
	//ActionBar->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	RefreshSlots();
}

// Called every frame
void APaintingPicker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APaintingPicker::RefreshSlots()
{
	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	UPainterSaveGameIndex* SaveGameIndex = UPainterSaveGameIndex::Load();
	if (Grid && SaveGameIndex)
	{
		Grid->ClearPaginationDots();
		Grid->AddPaginationDot(true);
		Grid->AddPaginationDot(false);
		Grid->AddPaginationDot(false);

		Grid->ClearCards();
		int32 Index = 0;
		for (FString SlotName : SaveGameIndex->GetSlotNames())
		{
			Grid->AddPainting(this, Index++, SlotName);
		}
		Grid->AddNewButton(this, Index++);
	}
}

void APaintingPicker::AddPainting()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UPainterSaveGame* NewPainting = UPainterSaveGame::Create();
	if (NewPainting)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Canvas", true, "SlotName=" + NewPainting->GetSlotName());
	}	
	RefreshSlots();
	UStereoLayerFunctionLibrary::HideSplashScreen();
}

void APaintingPicker::DeletePainting(FString SlotName)
{
	UE_LOG(LogTemp, Warning, TEXT("Deleting: %s"), *SlotName);
	if (UPainterSaveGame::Delete(SlotName))	RefreshSlots();
}
