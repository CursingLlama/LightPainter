// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.generated.h"

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStroke();

	void Update(FVector CursorLocation);
		
private:
	
	//Config
	UPROPERTY(EditDefaultsOnly) class UStaticMesh* SplineMesh;
	UPROPERTY(EditDefaultsOnly) class UMaterialInterface* SplineMaterial;

	//Components
	UPROPERTY(VisibleAnywhere) class USceneComponent* Root = nullptr;

	//State
	UPROPERTY() FVector PreviousCursorLocation;

	//Functions
	class USplineMeshComponent* CreateSplineMesh();
};
