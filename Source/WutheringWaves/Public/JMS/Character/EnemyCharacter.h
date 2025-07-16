// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "RootMotionModifier.h"
#include "Common/Characters/WWCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyAttributeSet;
class UWidgetComponent;
struct FEnemyAttackCollisionInfo;
class UEnemyCombatComponent;
class UBoxComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitializedDelegate);

UCLASS()
class WUTHERINGWAVES_API AEnemyCharacter : public AWWCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnemyAttributeSet* EnemyAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UWidgetComponent* WidgetComponent;

	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Motion Warping")
	void SetAttackTransformFromMotionWarpingTarget(FName WarpTargetName);

	UPROPERTY(BlueprintAssignable)
	FOnInitializedDelegate OnInitialized;

private:
	void InitEnemyStartUpData();
};
