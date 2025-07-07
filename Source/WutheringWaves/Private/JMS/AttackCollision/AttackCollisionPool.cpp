// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AttackCollision/AttackCollisionPool.h"

#include "JMS/AttackCollision/EnemyAttackCollision_Box.h"
#include "JMS/AttackCollision/EnemyAttackCollision_Capsule.h"
#include "JMS/AttackCollision/EnemyAttackCollision_Sphere.h"

// Sets default values
AAttackCollisionPool::AAttackCollisionPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
