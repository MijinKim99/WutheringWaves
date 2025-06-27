// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WWAnimInstance.h"
#include "PlayerLinkedAnimLayer.generated.h"

class UPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class WWCOPY_API UPlayerLinkedAnimLayer : public UWWAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UPlayerAnimInstance* GetPlayerAnimInstance() const;
};
