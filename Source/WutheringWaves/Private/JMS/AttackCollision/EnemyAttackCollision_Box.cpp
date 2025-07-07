// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AttackCollision/EnemyAttackCollision_Box.h"

#include "Common/WWDebugHelper.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AEnemyAttackCollision_Box::AEnemyAttackCollision_Box()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEnemyAttackCollision_Box::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyAttackCollision_Box::OnBeginOverlap);
}

void AEnemyAttackCollision_Box::AttackAsProjectile(const FVector& TargetLocation, const FVector& BoxExtent)
{
	// 충돌 델리게이트 바인딩
	// 크기 세팅 (Box만 가능)
	BoxComponent->SetBoxExtent(BoxExtent);
	// 발사
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileMovementComponent->AddForce((TargetLocation - GetActorLocation()) * 1000.0f);
}

void AEnemyAttackCollision_Box::ResetCollision()
{
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMovementComponent->StopMovementImmediately();
	SetActorRelativeTransform(InitialRelativeTransform);
}

void AEnemyAttackCollision_Box::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult& SweepResult)
{
	Debug::Print(FString::Printf(TEXT("Collision Begin Overlap : %s"), *OtherActor->GetActorNameOrLabel()));
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (OtherPawn)
	{
		IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
		if (OtherTeamAgent)
		{
			if (OtherTeamAgent->GetGenericTeamId() != InstigatorTeamId)
			{
				OnHitTargetActor(OtherActor);
			}
		}
		else
		{
			ResetCollision();
		}
	}
}
