// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AttackCollision/EnemyAttackCollision_Capsule.h"

#include "Components/CapsuleComponent.h"

AEnemyAttackCollision_Capsule::AEnemyAttackCollision_Capsule()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CapsuleComponent->SetCapsuleRadius(100.0f);
}

void AEnemyAttackCollision_Capsule::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyAttackCollision::OnBeginOverlap);
}
