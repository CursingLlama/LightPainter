// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"

#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"



void UPaintingGrid::AddPainting()
{
	if (!(PaintingGrid || GridCardClass)) return;
	
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);
	USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(0));
	if (SizeBox)
	{
		SizeBox->AddChild(NewWidget);
	}	
}
