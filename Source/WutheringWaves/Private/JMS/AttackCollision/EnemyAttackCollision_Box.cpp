// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AttackCollision/EnemyAttackCollision_Box.h"

#include "Components/BoxComponent.h"

AEnemyAttackCollision_Box::AEnemyAttackCollision_Box()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetBoxExtent(FVector(100.0f));
}

void AEnemyAttackCollision_Box::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this,&AEnemyAttackCollision::OnBeginOverlap);
}
