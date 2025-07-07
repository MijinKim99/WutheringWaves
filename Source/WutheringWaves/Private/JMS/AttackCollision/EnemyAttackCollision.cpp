// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AttackCollision/EnemyAttackCollision.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEnemyAttackCollision::AEnemyAttackCollision()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->bIsHomingProjectile = false;
}

// Called when the game starts or when spawned
void AEnemyAttackCollision::BeginPlay()
{
	Super::BeginPlay();

	InstigatorTeamId = Cast<IGenericTeamAgentInterface>(Cast<APawn>(GetParentActor())->GetController())->
		GetGenericTeamId();
	InitialRelativeTransform = GetActorTransform().GetRelativeTransform(GetParentActor()->GetActorTransform());
}

void AEnemyAttackCollision::SetGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
}


void AEnemyAttackCollision::OnHitTargetActor(AActor* HitActor)
{
	// 중복 검사
	if (HitTargetSet.Contains(HitActor))
	{
		return;
	}

	HitTargetSet.Add(HitActor);

	// GameplayEffectSpecHandle 적용
	UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(HitActor, GameplayEffectSpecHandle);

	// Gameplay Event 전달
	FGameplayEventData Data;
	Data.Instigator = GetInstigator();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, WWGameplayTags::Shared_Event_HitReact, Data);
	ResetCollision();
}

void AEnemyAttackCollision::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	// 자식에서 구현
}

void AEnemyAttackCollision::AttackAsProjectile(const FVector& TargetLocation, const FVector& BoxExtent)
{
	// 자식에서 구현
}


void AEnemyAttackCollision::ResetCollision()
{
	//자식에서 구현
}
