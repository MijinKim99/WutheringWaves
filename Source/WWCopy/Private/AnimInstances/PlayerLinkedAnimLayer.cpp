// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/PlayerLinkedAnimLayer.h"

#include "AnimInstances/Player/PlayerAnimInstance.h"

UPlayerAnimInstance* UPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
