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

	PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	Refresh();
}

// Called every frame
void APaintingPicker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void APaintingPicker::Refresh()
{
	RefreshDots();
	RefreshSlots();
}

void APaintingPicker::RefreshSlots()
{
	UPainterSaveGameIndex* SaveGameIndex = UPainterSaveGameIndex::Load();
	if (PaintingGridWidget && SaveGameIndex)
	{
		PaintingGridWidget->ClearCards();

		int32 StartOffset = CurrentPage * PaintingGridWidget->SlotsPerPage();
		int32 SlotsOnPage = FMath::Clamp<int32>(SaveGameIndex->GetSlotNames().Num() - StartOffset, 0, PaintingGridWidget->SlotsPerPage());
		for (int32 i = 0; i < SlotsOnPage; i++)
		{
			PaintingGridWidget->AddPainting(this, i, SaveGameIndex->GetSlotNames()[StartOffset + i]);
		}
		if (SlotsOnPage < PaintingGridWidget->SlotsPerPage())
		{
			PaintingGridWidget->AddNewButton(this, SlotsOnPage);
		}
	}
}

void APaintingPicker::RefreshDots()
{
	if (PaintingGridWidget)
	{
		PaintingGridWidget->ClearPaginationDots();
		for (int32 i = 0; i < GetNumberOfPages(); i++)
		{
			PaintingGridWidget->AddPaginationDot(i == CurrentPage);
		}
	}	
}

int32 APaintingPicker::GetNumberOfPages() const
{
	UPainterSaveGameIndex* SaveGameIndex = UPainterSaveGameIndex::Load();
	if (!SaveGameIndex || !PaintingGridWidget) return -1;

	int32 NumberOfSlots = SaveGameIndex->GetSlotNames().Num() + 1;
	return FMath::DivideAndRoundUp(NumberOfSlots, PaintingGridWidget->SlotsPerPage());
}

void APaintingPicker::AddPainting()
{
	//UStereoLayerFunctionLibrary::ShowSplashScreen();
	UPainterSaveGame* NewPainting = UPainterSaveGame::Create();
	/*if (NewPainting)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Canvas", true, "SlotName=" + NewPainting->GetSlotName());
	}*/
	Refresh();
	//UStereoLayerFunctionLibrary::HideSplashScreen();
}

void APaintingPicker::DeletePainting(FString SlotName)
{
	if (UPainterSaveGame::Delete(SlotName))	Refresh();
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp<int32>(CurrentPage + Offset, 0, GetNumberOfPages() - 1);
	Refresh();
}
