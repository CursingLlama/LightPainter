// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewPaintingGridCard.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UNewPaintingGridCard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	bool Initialize() override;
	void SetPaintingPicker(class APaintingPicker* NewPaintingPicker);
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget)) class UButton* AddButton;

private:

	//Config
	UPROPERTY() class APaintingPicker* PaintingPicker;

	//Functions
	UFUNCTION() void AddButtonClicked();
};
