// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AnimInstance/EnemyAnimInstance.h"

#include "Common/Characters/WWCharacter.h"

void UEnemyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	Velocity = OwningCharacter->GetVelocity();
}
