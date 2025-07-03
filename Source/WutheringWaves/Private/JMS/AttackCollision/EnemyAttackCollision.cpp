// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AttackCollision/EnemyAttackCollision.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"

// Sets default values
AEnemyAttackCollision::AEnemyAttackCollision()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void AEnemyAttackCollision::BeginPlay()
{
	Super::BeginPlay();
	InstigatorTeamId = Cast<IGenericTeamAgentInterface>(GetInstigator()->GetController())->GetGenericTeamId();
	CheckHitTargetOnSpawn();
	GetWorld()->GetTimerManager().SetTimer(CollisionActivationTimerHandle, this,
	                                       &AEnemyAttackCollision::DestroyCollision, CollisionDuration,
	                                       false);
}

void AEnemyAttackCollision::SetGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
}

void AEnemyAttackCollision::CheckHitTargetOnSpawn()
{
	Debug::Print(FString::Printf(TEXT("Collision Spawned : %s"), *GetActorTransform().ToString()));
}

void AEnemyAttackCollision::DestroyCollision()
{
	Destroy();
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
	ApplyGameplayEffectSpecHandleToTarget(HitActor, GameplayEffectSpecHandle);

	// Gameplay Event 전달
	FGameplayEventData Data;
	Data.Instigator = GetInstigator();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, WWGameplayTags::Shared_Event_HitReact, Data);
}

FActiveGameplayEffectHandle AEnemyAttackCollision::ApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(ASC&&InGameplayEffectSpecHandle.IsValid());

	return ASC->ApplyGameplayEffectSpecToTarget(*InGameplayEffectSpecHandle.Data, ASC);
}

void AEnemyAttackCollision::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	Debug::Print(FString::Printf(TEXT("Collision Begin Overlap : %s"), *OtherActor->GetActorNameOrLabel()));
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn)
	{
		return;
	}
	IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (!OtherTeamAgent)
	{
		return;
	}
	if (OtherTeamAgent->GetGenericTeamId() != InstigatorTeamId)
	{
		OnHitTargetActor(OtherActor);
	}
}
