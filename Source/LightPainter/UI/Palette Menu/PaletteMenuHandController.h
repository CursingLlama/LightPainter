// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"
#include "PaletteMenuHandController.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API APaletteMenuHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	APaletteMenuHandController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:

	//Components
	UPROPERTY(VisibleAnywhere) class UWidgetComponent* PaletteMenu;
	
};
