// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"

#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"


// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("Stroke Mesh"));
	StrokeMeshes->SetupAttachment(Root);

	JointMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("Joint Mesh"));
	JointMeshes->SetupAttachment(Root);
}

void AStroke::Update(FVector CursorLocation)
{
	if (PreviousCursorLocation != FVector::ZeroVector)
	{
		if (StrokeMeshes)
		{
			StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
		}		
	}	
	if (JointMeshes)
	{
		JointMeshes->AddInstance(FTransform(GetActorTransform().InverseTransformPosition(CursorLocation)));
	}
	PreviousCursorLocation = CursorLocation;
}

FStrokeState AStroke::SerializeToStruct() const
{
	FStrokeState State;
	State.Class = this->GetClass();
	for (int i = 0; i < JointMeshes->GetInstanceCount(); i++)
	{
		FTransform Transform;
		JointMeshes->GetInstanceTransform(i, Transform, true);
		State.Vertices.Emplace(Transform.GetLocation());
	}
	return State;
}

AStroke* AStroke::SpawnFromStruct(UWorld* World, const FStrokeState & StrokeState)
{
	AStroke* Stroke = World->SpawnActor<AStroke>(StrokeState.Class);
	if (Stroke)
	{
		for (FVector Location : StrokeState.Vertices)
		{
			Stroke->Update(Location);
		}
		return Stroke;
	}
	return nullptr;
}

FTransform AStroke::GetNextSegmentTransform(FVector CurrentLocation)
{
	FTransform NewTransform;

	NewTransform.SetLocation(GetActorTransform().InverseTransformPosition(PreviousCursorLocation));
	
	FVector StartNormal = PreviousCursorLocation.ForwardVector.GetSafeNormal();
	FVector EndNormal = (CurrentLocation - PreviousCursorLocation).GetSafeNormal();
	NewTransform.SetRotation(FQuat::FindBetweenNormals(StartNormal, EndNormal));
	
	NewTransform.SetScale3D(FVector((CurrentLocation - PreviousCursorLocation).Size(), 1, 1));

	return NewTransform;
}
