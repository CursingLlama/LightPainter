// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGridCard.h"
#include "PaintingPicker.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UPaintingGridCard::Initialize()
{
	if (Super::Initialize())
	{
		CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
		DeleteButton->OnClicked.AddDynamic(this, &UPaintingGridCard::DeleteButtonClicked);
		return true;
	}	
	return false;
}

void UPaintingGridCard::SetPaintingPicker(APaintingPicker * NewPaintingPicker)
{
	PaintingPicker = NewPaintingPicker;
}

void UPaintingGridCard::SetPaintingName(FString InPaintingName)
{
	PaintingName = InPaintingName;
	SlotName->SetText(FText::FromString(PaintingName));	
}

void UPaintingGridCard::CardButtonClicked()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), "Canvas", true, "SlotName=" + PaintingName);	
}

void UPaintingGridCard::DeleteButtonClicked()
{
	PaintingPicker->DeletePainting(PaintingName);
}
