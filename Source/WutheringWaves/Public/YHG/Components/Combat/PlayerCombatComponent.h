// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Components/Combat/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class APlayerWeapon;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UPlayerCombatComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	APlayerWeapon* Weapon;
};
