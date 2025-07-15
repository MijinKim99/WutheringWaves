// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Common/ObjectPool/WWPooledObject.h"
#include "AttackCollisionCapsule.generated.h"

class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AAttackCollisionCapsule : public AWWPooledObject
{
	GENERATED_BODY()

	AAttackCollisionCapsule();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Components
	UPROPERTY(EditAnywhere, Category = "Component")
	UCapsuleComponent* CapsuleComponent;

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
	FGameplayTag FXGameplayCueTag;

	// Event To Send
	FGameplayTag HitReactEventTag;
	UFUNCTION(BlueprintCallable, Category = "Attack Capsule")
	void InitializeAndAttackWithCapsule(float Duration, float Radius, float HalfHeight, FVector Location, FRotator Rotation,
	                       const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle, FGameplayTag InFXGameplayCueTag,
	                       FGameplayTag InHitReactEventTag);
};
