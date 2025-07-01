// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Characters/WWCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEnemyCharacter : public AWWCharacter
{
	GENERATED_BODY()
AEnemyCharacter();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(EditAnywhere, Category ="Combat")
	UBoxComponent* AttackCollisionBox;
};
