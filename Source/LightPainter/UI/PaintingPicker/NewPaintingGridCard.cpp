// Fill out your copyright notice in the Description page of Project Settings.

#include "NewPaintingGridCard.h"
#include "PaintingPicker.h"

#include "Components/Button.h"


bool UNewPaintingGridCard::Initialize()
{
	if (Super::Initialize())
	{
		AddButton->OnClicked.AddDynamic(this, &UNewPaintingGridCard::AddButtonClicked);
		return true;
	}
	return false;
}

void UNewPaintingGridCard::SetPaintingPicker(APaintingPicker* NewPaintingPicker)
{
	PaintingPicker = NewPaintingPicker;
}

void UNewPaintingGridCard::AddButtonClicked()
{
	if (PaintingPicker)
	{
		PaintingPicker->AddPainting();
	}	
}
