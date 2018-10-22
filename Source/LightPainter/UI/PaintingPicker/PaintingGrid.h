// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) void AddPainting(class APaintingPicker* PaintingPicker, int32 Index, FString PaintingName);
	UFUNCTION(BlueprintCallable) void AddNewButton(class APaintingPicker* PaintingPicker, int32 Index);
	UFUNCTION(BlueprintCallable) void ClearCards();
	UFUNCTION(BlueprintCallable) void AddPaginationDot(bool bIsActive);
	UFUNCTION(BlueprintCallable) void ClearPaginationDots();
	UFUNCTION(BlueprintCallable) int32 SlotsPerPage() const;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget)) class UUniformGridPanel* PaintingGrid = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget)) class UHorizontalBox* PaginationDots = nullptr;
	
private:
	UPROPERTY(EditDefaultsOnly) float PaginationDotPadding = 8;
	
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UPaintingGridCard> GridCardClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UNewPaintingGridCard> NewGridCardClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UPaginationDot> PaginationDotClass;
};
