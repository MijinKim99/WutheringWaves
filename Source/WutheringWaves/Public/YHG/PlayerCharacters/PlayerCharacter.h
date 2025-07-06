// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Characters/WWCharacter.h"
#include "PlayerCharacter.generated.h"

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
	APlayerCharacter();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* PlayerCombatComponent;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;

public:
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }

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
	bool bIsJumping;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsLeftJumping;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRightJumping;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool AttackMode;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	int32 LightAttackComboCount;
	
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
};