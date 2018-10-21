// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"
#include "PaintingGridCard.h"
#include "NewPaintingGridCard.h"

#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"



void UPaintingGrid::AddPainting(class APaintingPicker* PaintingPicker, int32 Index, FString PaintingName)
{
	if (!(PaintingGrid || GridCardClass)) return;
	
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
	if (!(PaintingGrid || NewGridCardClass)) return;

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
