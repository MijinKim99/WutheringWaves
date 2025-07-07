// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "RootMotionModifier.h"
#include "Common/Characters/WWCharacter.h"
#include "EnemyCharacter.generated.h"

struct FEnemyAttackCollisionInfo;
class UEnemyCombatComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEnemyCharacter : public AWWCharacter
{
	GENERATED_BODY()
AEnemyCharacter();
public:
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

public:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Attack
	void SetAttackCollisionAtLocation(const FVector& Location, float Duration,const FVector& BoxExtent);
	void LaunchAttackCollisionAsProjectile(const FVector& TargetLocation, const FVector& BoxExtent);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(EditAnywhere, Category ="Combat")
	UBoxComponent* AttackCollisionBox;
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	virtual void BeginPlay() override;

	// Attack
	FTimerHandle CollisionActivationTimerHandle;
	void DisableAttackCollision();

	UFUNCTION(BlueprintCallable, Category = "Motion Warping")
	void SetAttackTransformFromMotionWarpingTarget(FName WarpTargetName);
	
private:
	void InitEnemyStartUpData();
};
