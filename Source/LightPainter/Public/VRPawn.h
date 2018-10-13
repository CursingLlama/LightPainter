// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// Config
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<class AHandController> HandControllerClass;
	

	// Components
	UPROPERTY(VisibleAnywhere) USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere) class UCameraComponent* Camera;

	// Reference
	UPROPERTY()	AHandController* RightHand;
	UPROPERTY()	AHandController* LeftHand;
	
	//Fuctions
	void AdjustForPlaySpace();

	void RightTriggerPressed();
	void RightTriggerReleased();
};