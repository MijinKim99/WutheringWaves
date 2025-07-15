// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "Common/ObjectPool/WWPooledObject.h"
#include "AttackCollisionCapsuleInstance.generated.h"

class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AAttackCollisionCapsuleInstance : public AWWPooledObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackCollisionCapsuleInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// AWWPooledObject
	virtual void SetActive(bool IsActive, APawn* InInstigator) override;
	virtual void Deactivate() override;
	UPROPERTY(EditAnywhere, Category = "Component")
	UCapsuleComponent* CapsuleComponent;

	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	

	FGenericTeamId InstigatorTeamId;
	
	// Event To Send
	FGameplayTag HitReactEventTag;
public:
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void AttackOverlappingEnemies(const FVector& TargetLocation);
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void SetCapsuleSize(float InRadius, float InHalfHeight);
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void SetHitReactEventTag(FGameplayTag InGameplayEventTag);
};
