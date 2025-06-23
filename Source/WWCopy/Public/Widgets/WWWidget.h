// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WWWidget.generated.h"

class UPlayerUIComponent;
/**
 * 
 */
UCLASS()
class WWCOPY_API UWWWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent);

};
