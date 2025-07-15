// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Common/ObjectPool/WWPooledObject.h"
#include "GameFramework/Actor.h"
#include "AttackCollisionSphereProjectile.generated.h"

class USphereComponent;
struct FGameplayCueParameters;
struct FGameplayTag;
class AWWCharacter;
class UProjectileMovementComponent;
class UBoxComponent;


UCLASS()
class WUTHERINGWAVES_API AAttackCollisionSphereProjectile : public AWWPooledObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackCollisionSphereProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, Category = "Component")
	USphereComponent* SphereComponent;

	// AWWPooledObject
	virtual void SetActive(bool IsActive, APawn* InInstigator) override;
	virtual void Deactivate() override;

	// Attack
	TSet<AActor*> HitTargetSet;
	void OnHitTargetActor(AActor* HitActor);
	FGameplayEffectSpecHandle GameplayEffectSpecHandle;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse, const FHitResult& Hit);
	FGenericTeamId InstigatorTeamId;

	// FX
	FGameplayTag ProjectileGameplayCueTag;
	FGameplayTag ExplosionGameplayCueTag;

	// Event To Send
	FGameplayTag HitReactEventTag;

public:
	// 콜리전 크기, 위치, GameplayCue 지정해준 후에 호출해야함
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void LaunchProjectile(const FVector& TargetLocation, float Power);
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void SetSphereRadius(float InRadius);
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void SetProjectileGameplayCueTag(FGameplayTag InGameplayCueTag);
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void SetExplosionGameplayCueTag(FGameplayTag InGameplayCueTag);
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void SetHitReactEventTag(FGameplayTag InGameplayEventTag);
};
