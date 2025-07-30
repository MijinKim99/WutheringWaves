// Fill out your copyright notice in the Description page of Project Settings.



#include "Common/AnimInstances/CharacterAnimInstance.h"
#include "Common/Components/Combat/PawnCombatComponent.h"
#include "Common/AnimInstances/CharacterAnimInstance.h"
#include "Common/Characters/WWCharacter.h"
#include "Common/WWDebugHelper.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwningCharacter = Cast<AWWCharacter>(TryGetPawnOwner());
	if (!OwningCharacter)
	{
		//Debug::Print(TEXT("CharacterAnimInstance : Cast Failed OwningCharacter"));
		return;
	}
	
	OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	if (!OwningMovementComponent)
	{
		//Debug::Print(TEXT("CharacterAnimInstance : Can't find CharacterMovement"));
		return;
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	//소유한 캐릭터의 속도(x, y만 고려)
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	//소유한 캐릭터무브먼트의 움직임
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
