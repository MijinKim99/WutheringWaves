// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "Common/ObjectPool/WWPooledObject.h"
#include "AttackCollisionSphereInstance.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class WUTHERINGWAVES_API AAttackCollisionSphereInstance : public AWWPooledObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackCollisionSphereInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// AWWPooledObject
	virtual void SetActive(bool IsActive, APawn* InInstigator) override;
	virtual void Deactivate() override;
	UPROPERTY(EditAnywhere, Category = "Component")
	USphereComponent* SphereComponent;

	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	

	FGenericTeamId InstigatorTeamId;
	
	// Event To Send
	FGameplayTag HitReactEventTag;
public:
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void AttackOverlappingEnemies(const FVector& TargetLocation);
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void SetSphereRadius(float InRadius);
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);
	UFUNCTION(BlueprintCallable, Category = "SphereInstance")
	void SetHitReactEventTag(FGameplayTag InGameplayEventTag);
};
