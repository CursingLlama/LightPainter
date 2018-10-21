// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"
#include "PainterSaveGameIndex.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"


UPainterSaveGame* UPainterSaveGame::Create() 
{
	UPainterSaveGame* GameSave = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	GameSave->SlotName = FGuid::NewGuid().ToString();
	if (!GameSave->Save()) return nullptr;
	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	Index->AddSaveGame(GameSave);
	Index->Save();
	return GameSave;
}

bool UPainterSaveGame::Delete(FString Slot)
{
	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	if (!Index) return false;
	if (!UGameplayStatics::DeleteGameInSlot(Slot, 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to delete %s file."), *Slot);
		return false;
	}
	if (!Index->RemoveSaveGame(Slot))
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to remove %s from save game index."), *Slot);
		return false;
	}	
	return true;
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
