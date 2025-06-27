// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/CharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Characters/WWCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	//TryGetPawnOwner 소유자의 Pawn을 반환
	OwningCharacter = Cast<AWWCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	// Character, MovementComponent Null 체크
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	// 속력
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	// 가속 중 여부
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	// 이동방향
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
