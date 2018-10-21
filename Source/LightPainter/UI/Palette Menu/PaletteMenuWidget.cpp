// Fill out your copyright notice in the Description page of Project Settings.

#include "PaletteMenuWidget.h"

#include "Components/Button.h"

bool UPaletteMenuWidget::Initialize()
{
	if (Super::Initialize())
	{
		BackButton->OnClicked.AddDynamic(this, &UPaletteMenuWidget::BackButtonPressed);
		UE_LOG(LogTemp, Warning, TEXT("back button bound"));
		return true;
	}
	return false;
}

void UPaletteMenuWidget::BackButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Back button pressed"));
}
