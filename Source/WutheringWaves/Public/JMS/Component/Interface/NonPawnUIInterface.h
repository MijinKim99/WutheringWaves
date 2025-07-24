// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NonPawnUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNonPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WUTHERINGWAVES_API INonPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetNonPawnUIComponent() const = 0;
};
