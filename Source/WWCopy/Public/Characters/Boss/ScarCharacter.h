// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWCopy/Public/Characters/Boss/BossCharacterBase.h"
#include "ScarCharacter.generated.h"

/**
 * 
 */
UCLASS()
class WWCOPY_API AScarCharacter : public ABossCharacterBase
{
	GENERATED_BODY()
	AScarCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
