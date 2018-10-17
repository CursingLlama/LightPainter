// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"


#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EngineUtils.h"


UPainterSaveGame* UPainterSaveGame::Create() 
{
	return Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
}

UPainterSaveGame* UPainterSaveGame::Load()
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("Test"), 0));
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, FString("Test"), 0);
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
