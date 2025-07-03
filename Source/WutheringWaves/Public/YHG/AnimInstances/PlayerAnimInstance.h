// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AnimInstances/CharacterAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerLocomotion")
	FVector2D MoveValue;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerLocomotion")
	bool bFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerLocomotion")
	bool bGrounded;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
