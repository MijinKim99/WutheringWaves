// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AttackCollision/EnemyAttackCollision_Sphere.h"

#include "Components/SphereComponent.h"

AEnemyAttackCollision_Sphere::AEnemyAttackCollision_Sphere()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetSphereRadius(100.0f);
	
}

void AEnemyAttackCollision_Sphere::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this,&AEnemyAttackCollision::OnBeginOverlap);
}
