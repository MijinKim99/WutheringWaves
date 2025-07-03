// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/AttackCollision/EnemyAttackCollision.h"
#include "EnemyAttackCollision_Box.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEnemyAttackCollision_Box : public AEnemyAttackCollision
{
	GENERATED_BODY()
	AEnemyAttackCollision_Box();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AttackCollision")
	UBoxComponent* BoxComponent;
	virtual void BeginPlay() override;
};
