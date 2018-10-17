// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.generated.h"

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()

	UPROPERTY() TSubclassOf<class AStroke> Class;
	UPROPERTY() TArray<FVector> Vertices;
};

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStroke();

	void Update(FVector CursorLocation);

	FStrokeState SerializeToStruct() const;
	static AStroke* SpawnFromStruct(UWorld* World, const FStrokeState& StrokeState);
		
private:
	
	//Components
	UPROPERTY(VisibleAnywhere) class USceneComponent* Root = nullptr;
	UPROPERTY(VisibleAnywhere) class UInstancedStaticMeshComponent* StrokeMeshes = nullptr;
	UPROPERTY(VisibleAnywhere) class UInstancedStaticMeshComponent* JointMeshes = nullptr;

	//State
	UPROPERTY() FVector PreviousCursorLocation = FVector::ZeroVector;

	//Functions
	FTransform GetNextSegmentTransform(FVector CurrentLocation);

};
