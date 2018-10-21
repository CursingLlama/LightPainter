// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetTouchingComponent.h"

UWidgetTouchingComponent::UWidgetTouchingComponent()
{

}

void UWidgetTouchingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	if (IsOverInteractableWidget() && !bHasClicked)
	{
		bHasClicked = true;
		PressPointerKey(EKeys::LeftMouseButton);	
	}
	if (!IsOverInteractableWidget() && bHasClicked)
	{
		bHasClicked = false;
		ReleasePointerKey(EKeys::LeftMouseButton);
	}
}
