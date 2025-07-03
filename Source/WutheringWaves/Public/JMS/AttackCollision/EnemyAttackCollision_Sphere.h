// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/AttackCollision/EnemyAttackCollision.h"
#include "EnemyAttackCollision_Sphere.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEnemyAttackCollision_Sphere : public AEnemyAttackCollision
{
	GENERATED_BODY()
	AEnemyAttackCollision_Sphere();

protected:
	UPROPERTY(EditDefaultsOnly, Category="AttackCollision")
	USphereComponent* SphereComponent;
	virtual void BeginPlay() override;
};
