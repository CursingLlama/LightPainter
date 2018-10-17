// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandControllerBase.generated.h"

UCLASS()
class LIGHTPAINTER_API AHandControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandControllerBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetHand(FName Hand);

	virtual void TriggerPressed();
	virtual void TriggerReleased();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Components
	UPROPERTY(VisibleAnywhere) class UMotionControllerComponent* MotionController;
	
};
