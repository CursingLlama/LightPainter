// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "HandControllerBase.h"
#include "Stroke.h"
#include "PaintingGameMode.h"
#include "UI/PaintingPicker/PaintingPicker.h"
#include "Saving/PainterSaveGame.h"

#include "Engine/World.h"
#include "EngineUtils.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

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

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Paint"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(FName("Paint"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);

	PlayerInputComponent->BindAxis(FName("Paginate"), this, &AVRPawn::PaginateAxisInput);

	PlayerInputComponent->BindAction(FName("Save"), EInputEvent::IE_Released, this, &AVRPawn::Save);
	//PlayerInputComponent->BindAction(FName("Load"), EInputEvent::IE_Released, this, &AVRPawn::Load);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	//Adjust HMD position for Oculus Rift TO DO: check for nullptr issue with first line
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	VRRoot->SetRelativeLocation(FVector(0, 0, 35));
	
	RightHand = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
	if (RightHand)
	{
		RightHand->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHand->SetHand(FXRMotionControllerBase::RightHandSourceId);
	}

	LeftHand = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
	if (LeftHand)
	{
		LeftHand->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHand->SetHand(FXRMotionControllerBase::LeftHandSourceId);
	}
	
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

void AVRPawn::PaginateAxisInput(float AxisInput)
{
	if (AxisInput > AxisDeadZone && !bChangedPage)
	{
		bChangedPage = true;
		UpdateCurrentPage(1);
	}
	if (AxisInput < -AxisDeadZone && !bChangedPage)
	{
		bChangedPage = true;
		UpdateCurrentPage(-1);
	}
	if (AxisInput < AxisDeadZone && AxisInput > -AxisDeadZone) bChangedPage = false;
}

void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	for (TActorIterator<APaintingPicker> ActorItr(GetWorld()) ; ActorItr; ++ActorItr)
	{
		ActorItr->UpdateCurrentPage(Offset);
	}
}

void AVRPawn::Save()
{	
	APaintingGameMode* GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->Save();
		GameMode->QuitToMenu();
	}	
}
