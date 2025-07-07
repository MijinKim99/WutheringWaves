// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackCollisionPool.generated.h"

class AEnemyAttackCollision_Sphere;
class AEnemyAttackCollision_Capsule;
class AEnemyAttackCollision_Box;

UCLASS()
class WUTHERINGWAVES_API AAttackCollisionPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackCollisionPool();

protected:
	
};
