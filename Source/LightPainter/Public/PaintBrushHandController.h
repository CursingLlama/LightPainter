// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	APaintBrushHandController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TriggerPressed() override;
	void TriggerReleased() override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//Config
	UPROPERTY(EditAnywhere) TSubclassOf<class AStroke> StrokeClass;

	//State
	class AStroke* CurrentStroke = nullptr;
};
