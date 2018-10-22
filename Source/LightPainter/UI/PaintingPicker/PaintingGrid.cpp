// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"
#include "PaintingGridCard.h"
#include "NewPaintingGridCard.h"
#include "PaginationDot.h"

#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"



void UPaintingGrid::AddPainting(class APaintingPicker* PaintingPicker, int32 Index, FString PaintingName)
{
	if (!PaintingGrid || !GridCardClass) return;
	
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (NewWidget)
	{
		NewWidget->SetPaintingPicker(PaintingPicker);
		NewWidget->SetPaintingName(PaintingName);

		USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(Index));
		if (SizeBox)
		{
			SizeBox->ClearChildren();
			SizeBox->AddChild(NewWidget);
		}
	}	
}

void UPaintingGrid::AddNewButton(class APaintingPicker* PaintingPicker, int32 Index)
{
	if (!PaintingGrid || !NewGridCardClass) return;

	UNewPaintingGridCard* NewWidget = CreateWidget<UNewPaintingGridCard>(GetWorld(), NewGridCardClass);
	if (NewWidget)
	{
		NewWidget->SetPaintingPicker(PaintingPicker);
		USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(Index));
		if (SizeBox)
		{
			SizeBox->ClearChildren();
			SizeBox->AddChild(NewWidget);
		}
	}

}

void UPaintingGrid::ClearCards()
{
	for (int32 Index = 0; Index < SlotsPerPage(); Index++)
	{
		USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(Index));
		if (SizeBox)
		{
			SizeBox->ClearChildren();
		}
	}
	
}

void UPaintingGrid::AddPaginationDot(bool bIsActive)
{
	if (!PaginationDots || !PaginationDotClass) return;

	UPaginationDot* Dot = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotClass);
	if (Dot)
	{
		Dot->SetActive(bIsActive);
		
		UHorizontalBoxSlot* Slot = PaginationDots->AddChildToHorizontalBox(Dot);
		Slot->SetPadding(FMargin(PaginationDotPadding, 0));
	}
}

void UPaintingGrid::ClearPaginationDots()
{
	if (PaginationDots)
	{
		PaginationDots->ClearChildren();
	}
}

int32 UPaintingGrid::SlotsPerPage() const
{
	if (!PaintingGrid) return -1;
	return PaintingGrid->GetChildrenCount();
}
