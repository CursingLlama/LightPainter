// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Stroke.h"
#include "PainterSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	static UPainterSaveGame* Create();
	static bool Delete(FString Slot);
	static UPainterSaveGame* Load(FString Slot);

	bool Save();
	
	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);

	FString GetSlotName() const { return SlotName; }

private:

	void ClearWorld(UWorld* World);

	//State
	UPROPERTY() FString SlotName;
	UPROPERTY() TArray<FStrokeState> Strokes;
	
};
