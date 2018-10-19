// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaintingGridCard.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGridCard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetPaintingName(FString PaintingName);
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget)) class UTextBlock* SlotName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget)) class UButton* CardButton;

private:

	UFUNCTION() void CardButtonClicked();

	//State
	FString PaintingName;
};
