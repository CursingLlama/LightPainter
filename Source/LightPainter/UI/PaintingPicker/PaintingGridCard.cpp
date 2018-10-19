// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGridCard.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void UPaintingGridCard::SetPaintingName(FString InPaintingName)
{
	PaintingName = InPaintingName;
	SlotName->SetText(FText::FromString(PaintingName));

	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), "Canvas", false, "SlotName=" + PaintingName);
	UStereoLayerFunctionLibrary::HideSplashScreen();
}
