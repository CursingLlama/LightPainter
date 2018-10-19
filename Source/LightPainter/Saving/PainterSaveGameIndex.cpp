// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGameIndex.h"
#include "PainterSaveGame.h"

#include "Kismet/GameplayStatics.h"

const FString UPainterSaveGameIndex::SLOT_NAME = "SaveGameIndex";

UPainterSaveGameIndex * UPainterSaveGameIndex::Load()
{
	UPainterSaveGameIndex* Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::LoadGameFromSlot(SLOT_NAME, 0));
	if (!Index)
	{
		Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
		Index->Save();
	}
	return Index;
}

bool UPainterSaveGameIndex::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SLOT_NAME, 0);
}

void UPainterSaveGameIndex::AddSaveGame(UPainterSaveGame * SaveGame)
{
	SlotNameList.Emplace(SaveGame->GetSlotName());
}

TArray<FString> UPainterSaveGameIndex::GetSlotNames() const
{
	return SlotNameList;
}
