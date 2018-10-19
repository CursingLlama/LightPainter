// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"
#include "PaintingGridCard.h"

#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"



void UPaintingGrid::AddPainting(int32 Index, FString PaintingName)
{
	if (!(PaintingGrid || GridCardClass)) return;
	
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (NewWidget)
	{
		NewWidget->SetPaintingName(PaintingName);

		USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(Index));
		if (SizeBox)
		{
			SizeBox->AddChild(NewWidget);
		}
	}		
}
