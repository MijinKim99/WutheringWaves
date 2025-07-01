// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WWAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	bool OwnerHasTag(FGameplayTag Tag) const;
};
