// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RootMotionModifier.h"
#include "Common/Characters/WWCharacter.h"
#include "EnemyCharacter.generated.h"

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
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(EditAnywhere, Category ="Combat")
	UBoxComponent* AttackCollisionBox;
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Motion Warping")
	void SetAttackTransformFromMotionWarpingTarget(FName WarpTargetName);
	
private:
	void InitEnemyStartUpData();
	
};
