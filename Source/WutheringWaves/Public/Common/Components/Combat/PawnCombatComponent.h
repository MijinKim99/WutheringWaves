// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Components/WWPawnExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AWeaponBase;

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPawnCombatComponent : public UWWPawnExtensionComponent
{
	GENERATED_BODY()
public:
	// 공격 처리
	virtual void OnHitTagetActor(AActor* HitActor);

protected:
	//중복방지를 위한 배열
	TArray<AActor*> OverlappedActors;
	
};
