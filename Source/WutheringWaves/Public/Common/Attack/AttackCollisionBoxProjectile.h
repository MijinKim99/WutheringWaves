// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "Common/ObjectPool/WWPooledObject.h"
#include "AttackCollisionBoxProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AAttackCollisionBoxProjectile : public AWWPooledObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackCollisionBoxProjectile();
	UFUNCTION(BlueprintCallable)
	UProjectileMovementComponent* GetProjectileMovementComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, Category = "Component")
	UBoxComponent* BoxComponent;

	// AWWPooledObject
	virtual void SetActive(bool IsActive, APawn* InInstigator) override;
	virtual void Deactivate() override;

	// Attack
	TSet<AActor*> HitTargetSet;
	void OnHitTargetActor(AActor* HitActor);
	// 단일 이펙트 적용 함수를 위한 멤버변수
	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	// 여러 이펙트 적용 함수를 위한 멤버변수
	TArray<FGameplayEffectSpecHandle> MultipleGameplayEffectSpecHandles;

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
	UFUNCTION(BlueprintCallable, Category = "Attack Box Projectile")
	void InitializeProjectileWithPresetAndShoot(TSubclassOf<AAttackCollisionBoxProjectile> ProjectileClass,
	                                            USkeletalMeshComponent* InstigatorMesh,
	                                            FName AttachSocketName, AActor* HomingTargetActor,
	                                            const TArray<FGameplayEffectSpecHandle>&
	                                            InGameplayEffectSpecHandles,
	                                            FVector TargetLocation, float ProjectileSpeed,
	                                            bool bShowCollisionInGame,
	                                            float LineThickness,
	                                            bool InbExplodeOnHit,
	                                            float DurationForNotExplodingProjectile);

	// 콜리전 크기, 위치, GameplayCue 지정해준 후에 호출해야함

	void InitializeProjectileAndShoot_Internal(FVector BoxExtent,
	                                           const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles,
	                                           FVector StartRelativeLocation,
	                                           FVector TargetLocation, float ProjectileSpeed,
	                                           FGameplayTag InProjectileGameplayCueTag,
	                                           FGameplayTag InExplosionGameplayCueTag,
	                                           FGameplayTag InHitReactEventTag, bool bShowCollisionInGame,
	                                           float LineThickness, float InProjectileGravityScale, bool
	                                           InbExplodeOnHit, float DurationForNotExplodingProjectile
	);

	// Bone Socket에 붙여서 콜리전 활성화
	void InitializeAttachedProjectileAndShoot_Internal(FVector BoxExtent,
	                                                   USkeletalMeshComponent* InstigatorMesh,
	                                                   FName AttachSocketName,
	                                                   const TArray<FGameplayEffectSpecHandle>&
	                                                   InGameplayEffectSpecHandles,
	                                                   FVector TargetLocation, float ProjectileSpeed,
	                                                   FGameplayTag InProjectileGameplayCueTag,
	                                                   FGameplayTag InExplosionGameplayCueTag,
	                                                   FGameplayTag InHitReactEventTag,
	                                                   bool bShowCollisionInGame,
	                                                   float LineThickness,
	                                                   float InProjectileGravityScale,
	                                                   bool InbExplodeOnHit,
	                                                   float DurationForNotExplodingProjectile);

	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box Projectile")
	void InitializeProjectileAndShoot(FVector BoxExtent,
	                                  const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle,
	                                  FVector StartRelativeLocation,
	                                  FVector TargetLocation, float ProjectileSpeed,
	                                  FGameplayTag InProjectileGameplayCueTag, FGameplayTag InExplosionGameplayCueTag,
	                                  FGameplayTag InHitReactEventTag, bool bShowCollisionInGame, float LineThickness,
	                                  float InProjectileGravityScale, bool
	                                  InbExplodeOnHit, float DurationForNotExplodingProjectile
	);
	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box Projectile")
	void InitializeAttachedProjectileAndShoot(FVector BoxExtent,
	                                          USkeletalMeshComponent* InstigatorMesh,
	                                          FName AttachSocketName,
	                                          const FGameplayEffectSpecHandle& InGameplayEffectSpecHandles,
	                                          FVector TargetLocation, float ProjectileSpeed,
	                                          FGameplayTag InProjectileGameplayCueTag,
	                                          FGameplayTag InExplosionGameplayCueTag,
	                                          FGameplayTag InHitReactEventTag,
	                                          bool bShowCollisionInGame,
	                                          float LineThickness,
	                                          float InProjectileGravityScale,
	                                          bool InbExplodeOnHit,
	                                          float DurationForNotExplodingProjectile);


	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box Projectile")
	void InitializeProjectileAndShootMultipleEffects(FVector BoxExtent,
	                                                 const TArray<FGameplayEffectSpecHandle>&
	                                                 InGameplayEffectSpecHandles,
	                                                 FVector StartRelativeLocation,
	                                                 FVector TargetLocation, float ProjectileSpeed,
	                                                 FGameplayTag InProjectileGameplayCueTag,
	                                                 FGameplayTag InExplosionGameplayCueTag,
	                                                 FGameplayTag InHitReactEventTag, bool bShowCollisionInGame,
	                                                 float LineThickness, float InProjectileGravityScale, bool
	                                                 InbExplodeOnHit, float DurationForNotExplodingProjectile
	);

	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box Projectile")
	void InitializeAttachedProjectileAndShootMultipleEffects(FVector BoxExtent,
	                                                         USkeletalMeshComponent* InstigatorMesh,
	                                                         FName AttachSocketName,
	                                                         const TArray<FGameplayEffectSpecHandle>&
	                                                         InGameplayEffectSpecHandles,
	                                                         FVector TargetLocation, float ProjectileSpeed,
	                                                         FGameplayTag InProjectileGameplayCueTag,
	                                                         FGameplayTag InExplosionGameplayCueTag,
	                                                         FGameplayTag InHitReactEventTag,
	                                                         bool bShowCollisionInGame,
	                                                         float LineThickness,
	                                                         float InProjectileGravityScale,
	                                                         bool InbExplodeOnHit,
	                                                         float DurationForNotExplodingProjectile);

public:
	bool bExplodeOnHit = false;
};
