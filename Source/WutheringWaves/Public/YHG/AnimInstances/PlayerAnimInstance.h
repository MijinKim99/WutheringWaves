// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AnimInstances/WWAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerAnimInstance : public UWWAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override; //초기값 설정
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override; //업데이트시 최적화 시킬수 있는 함수

protected:
	UPROPERTY()
	class  APlayerCharacter* OwningCharacter;
	UPROPERTY()
	class UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	bool bHasAcceleration;
};
