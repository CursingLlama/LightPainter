// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "HandController.h"
#include "Stroke.h"
#include "Saving/PainterSaveGame.h"

#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "XRMotionControllerBase.h"
#include "HeadMountedDisplayFunctionLibrary.h"

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

	//Adjust HMD position for Oculus Rift TO DO: check for nullptr issue with first line
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	VRRoot->SetRelativeLocation(FVector(0, 0, 35));
	
	RightHand = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if (RightHand)
	{
		RightHand->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHand->SetHand(FXRMotionControllerBase::RightHandSourceId);
	}

	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	Painting->Save();
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AdjustForPlaySpace();

}

void AVRPawn::AdjustForPlaySpace()
{
	FVector CameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	CameraOffset.Z = 0;
	AddActorWorldOffset(CameraOffset);
	VRRoot->AddWorldOffset(-CameraOffset);
}

void AVRPawn::RightTriggerPressed() { RightHand->TriggerPressed(); }
void AVRPawn::RightTriggerReleased() { RightHand->TriggerReleased(); }

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Paint"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(FName("Paint"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);
}
