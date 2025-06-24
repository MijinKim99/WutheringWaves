// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/PlayerAnimInstance.h"
#include "Characters/Player/PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningCharacter)
	{
		OwningPlayerCharacter = Cast<APlayerCharacter>(OwningCharacter);
	}
}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	// 릴렉스 모드 처리
	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.0f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
	// 릴렉스 모드 처리
}
