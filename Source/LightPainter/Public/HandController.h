// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"

UCLASS()
class LIGHTPAINTER_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AHandController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetHand(FName Hand);

	void TriggerPressed();
	void TriggerReleased();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//Config
	UPROPERTY(EditAnywhere) TSubclassOf<class AStroke> StrokeClass;

	// Components
	UPROPERTY(VisibleAnywhere) class UMotionControllerComponent* MotionController;

	//State
	class AStroke* CurrentStroke = nullptr;
};
