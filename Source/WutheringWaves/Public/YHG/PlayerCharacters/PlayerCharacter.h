// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Characters/WWCharacter.h"
#include "PlayerCharacter.generated.h"

struct FGameplayTag;
class UAbilitySystemComponent;
class UResonatorAttributeSet;
class AEnemyCharacter;
class UCameraComponent;
class USpringArmComponent;
class UPlayerCombatComponent;

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API APlayerCharacter : public AWWCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UPlayerUIComponent* PlayerUI;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UResonatorAttributeSet* ResonatorAttributeSet;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;

protected:
	//AN이나, ANS같은 곳에서, 원하는 시점에 캔슬하기 위한 함수들 
	UFUNCTION(BlueprintCallable)
	void CancelPlayerActiveAbilities(UAbilitySystemComponent* ASC, FGameplayTag CancelTag);
	
	UFUNCTION(BlueprintCallable)
	void CancelPlayerAllActiveAbilities(UAbilitySystemComponent* ASC);

//StateControl
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsGrounded;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsFalling;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsIdle;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsLeftMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRightMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRun;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsLeftJumping;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRightJumping;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bCanAirDash;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bSprintMode;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bAttackMode;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	int32 DashCount;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bDashInitCheck;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	int32 LightAttackComboCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Attack")
	TSet<AEnemyCharacter*> LightAttackTargets;
	
public:
	UFUNCTION()
	bool GetIsGrounded() const;
	UFUNCTION()
	bool GetIsFalling() const;
	UFUNCTION()
	bool GetIsIdle() const;
	UFUNCTION()
	bool GetIsRightMoving() const;
	UFUNCTION()
	bool GetIsLeftMoving() const;
	UFUNCTION()
	bool GetIsRun() const;
	UFUNCTION()
	bool GetIsLeftJumping() const;
	UFUNCTION()
	bool GetIsRightJumping() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* FGroundDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* BGroundDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* FSuccessGroundDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* BSuccessGroundDash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* FAirDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* BAirDash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* RFJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* LFJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* RFRunJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* LFRunJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* RStopSprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* LStopSprint;
};