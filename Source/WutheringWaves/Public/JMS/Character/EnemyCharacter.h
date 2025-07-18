// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "RootMotionModifier.h"
#include "Common/Characters/WWCharacter.h"
#include "AbilitySystemInterface.h"
#include "EnemyCharacter.generated.h"

class UWWAttributeSet;
class UWWAbilitySystemComponent;
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
class WUTHERINGWAVES_API AEnemyCharacter : public AWWCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWWAbilitySystemComponent* WWAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnemyAttributeSet* EnemyAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWWAttributeSet* WWAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UWidgetComponent* WidgetComponent;

	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Motion Warping")
	void SetAttackTransformFromMotionWarpingTarget(FName WarpTargetName);

	UPROPERTY(BlueprintAssignable)
	FOnInitializedDelegate OnInitialized;

private:
	void InitEnemyStartUpData();

protected:
	//AN이나, ANS같은 곳에서, 원하는 시점에 캔슬하기 위한 함수들 
	UFUNCTION(BlueprintCallable)
	void CancelEnemyActiveAbilities(UAbilitySystemComponent* ASC, FGameplayTag CancelTag);
	
	UFUNCTION(BlueprintCallable)
	void CancelEnemyAllActiveAbilities(UAbilitySystemComponent* ASC);
};
