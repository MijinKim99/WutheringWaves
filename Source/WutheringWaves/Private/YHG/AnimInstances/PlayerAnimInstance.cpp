// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AnimInstances/PlayerAnimInstance.h"
#include "Common/WWDebugHelper.h"
#include "Common/PlayerControllers/WWPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
