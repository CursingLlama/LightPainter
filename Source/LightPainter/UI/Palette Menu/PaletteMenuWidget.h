// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaletteMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaletteMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	bool Initialize() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget)) class UButton* BackButton;

private:

	UFUNCTION() void BackButtonPressed();
	
};
