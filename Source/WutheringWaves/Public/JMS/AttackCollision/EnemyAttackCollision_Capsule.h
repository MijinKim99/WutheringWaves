// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/AttackCollision/EnemyAttackCollision.h"
#include "EnemyAttackCollision_Capsule.generated.h"

class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEnemyAttackCollision_Capsule : public AEnemyAttackCollision
{
	GENERATED_BODY()
	AEnemyAttackCollision_Capsule();
protected:
	UPROPERTY(EditDefaultsOnly, Category="AttackCollision")
	UCapsuleComponent* CapsuleComponent;
	virtual void BeginPlay() override;
};
