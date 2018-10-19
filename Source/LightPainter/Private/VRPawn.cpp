// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "HandControllerBase.h"
#include "Stroke.h"
#include "PaintingGameMode.h"
#include "Saving/PainterSaveGame.h"

#include "Engine/World.h"

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
	
	RightHand = GetWorld()->SpawnActor<AHandControllerBase>(HandControllerClass);
	if (RightHand)
	{
		RightHand->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHand->SetHand(FXRMotionControllerBase::RightHandSourceId);
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

void AVRPawn::Save()
{	
	APaintingGameMode* GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->Save();
		UStereoLayerFunctionLibrary::ShowSplashScreen();
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
		UStereoLayerFunctionLibrary::HideSplashScreen();
	}	
}
