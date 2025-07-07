// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AnimInstances/CharacterAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsGrounded;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsFalling;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsIdle;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsLeftMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsRightMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsRun;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsLeftJumping;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerStateControl", meta = (AllowPrivateAccess))
	bool bIsRightJumping;
	

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
