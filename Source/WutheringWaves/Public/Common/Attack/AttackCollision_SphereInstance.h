// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "Common/ObjectPool/WWPooledObject.h"
#include "AttackCollision_SphereInstance.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class WUTHERINGWAVES_API AAttackCollision_SphereInstance : public AWWPooledObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackCollision_SphereInstance();

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
public:
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void AttackOverlappingEnemies(const FVector& TargetLocation);
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void SetSphereRadius(float InRadius);
	UFUNCTION(BlueprintCallable, Category = "SphereProjectile")
	void SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);
};
