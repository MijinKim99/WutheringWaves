// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AnimInstances/PlayerAnimInstance.h"
#include "Common/WWDebugHelper.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<APlayerCharacter>(OwningCharacter);
	if (!PlayerCharacter)
	{
		//Debug::Print(TEXT("PlayerAnimInstance : Failed Cast PlayerCharacter"),FColor::Red,999);
		return;
	}
}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!PlayerCharacter)
	{
		//Debug::Print(TEXT("PlayerAnimInstance : Can't find PlayerCharacter by Update"),FColor::Red,1000);
		return;
	}
	bIsGrounded = PlayerCharacter->GetIsGrounded();
	bIsFalling = PlayerCharacter->GetIsFalling();
	bIsIdle = PlayerCharacter->GetIsIdle();
	bIsLeftMoving = PlayerCharacter->GetIsLeftMoving();
	bIsRightMoving = PlayerCharacter->GetIsRightMoving();
	bIsRun = PlayerCharacter->GetIsRun();
	bIsLeftJumping = PlayerCharacter->GetIsLeftJumping();
	bIsRightJumping = PlayerCharacter->GetIsRightJumping();
}