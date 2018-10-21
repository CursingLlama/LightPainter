// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaginationDot.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaginationDot : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	void SetActive(bool bActive);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget)) class UImage* DotImage;

private:

	//Config
	UPROPERTY(EditDefaultsOnly) float InactiveOpacity = 0.4f;
	
};
