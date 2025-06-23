// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWCopy/Public/Characters/WWCharacter.h"
#include "AbilitySystemInterface.h"
#include "BossCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class WWCOPY_API ABossCharacterBase : public AWWCharacter
{
	GENERATED_BODY()
public:
	ABossCharacterBase();

protected:

	virtual void PossessedBy(AController* NewController) override;
};
