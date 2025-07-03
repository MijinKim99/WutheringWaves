// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "EnemyAttackCollision.generated.h"


UCLASS()
class WUTHERINGWAVES_API AEnemyAttackCollision : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyAttackCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Attack Collision")
	float CollisionDuration = 1.0f;
	void SetGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);


	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	FTimerHandle CollisionActivationTimerHandle;
	void DestroyCollision();

	void CheckHitTargetOnSpawn();

	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	TSet<AActor*> HitTargetSet;
	void OnHitTargetActor(AActor* HitActor);
	FActiveGameplayEffectHandle ApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor,
	                                                                  const FGameplayEffectSpecHandle&
	                                                                  InGameplayEffectSpecHandle);
	FGenericTeamId InstigatorTeamId;
};
