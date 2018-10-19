// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGameIndex.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGameIndex : public USaveGame
{
	GENERATED_BODY()
	
public:
	
	static UPainterSaveGameIndex* Load();
	bool Save();

	void AddSaveGame(class UPainterSaveGame* SaveGame);
	TArray<FString> GetSlotNames() const;

	static const FString SLOT_NAME;

private:

	UPROPERTY() TArray<FString> SlotNameList;
};
