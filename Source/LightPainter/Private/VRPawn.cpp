// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "HandController.h"

#include "Engine/World.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	RightHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if (RightHandController)
	{
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}	
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	CameraOffset.Z = 0;
	AddActorWorldOffset(CameraOffset);
	VRRoot->AddWorldOffset(-CameraOffset);
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

