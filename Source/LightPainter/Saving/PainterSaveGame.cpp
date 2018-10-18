// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"


#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"


UPainterSaveGame* UPainterSaveGame::Create() 
{
	UPainterSaveGame* GameSave = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	GameSave->SlotName = FGuid::NewGuid().ToString();
	return GameSave;
}

UPainterSaveGame* UPainterSaveGame::Load(FString Slot)
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot, 0));
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	Strokes.Empty();
	
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		Strokes.Emplace(StrokeItr->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld * World)
{
	ClearWorld(World);
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnFromStruct(World, StrokeState);
	}
}

void UPainterSaveGame::ClearWorld(UWorld * World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
	}
}
