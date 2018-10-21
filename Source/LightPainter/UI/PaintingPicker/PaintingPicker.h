// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintingPicker.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintingPicker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintingPicker();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void AddPainting();
	void DeletePainting(FString SlotName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

private:	
	// Components
	UPROPERTY(VisibleAnywhere) class USceneComponent* Root = nullptr;
	UPROPERTY(VisibleAnywhere) class UWidgetComponent* PaintingGrid = nullptr;
	///UPROPERTY(VisibleAnywhere) class UWidgetComponent* ActionBar = nullptr;
		
	//Functions
	void RefreshSlots();
};
