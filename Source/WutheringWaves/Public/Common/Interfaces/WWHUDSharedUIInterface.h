// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WWHUDSharedUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,NotBlueprintable)
class UWWHUDSharedUIInterface : public UInterface
{
	GENERATED_BODY()
};

class UWWHUDSharedUIComponent;
/**
 * 
 */
class WUTHERINGWAVES_API IWWHUDSharedUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category="HUD Shared UI Interface")
	virtual UWWHUDSharedUIComponent* GetHUDSharedUIComponent() const = 0;
};
