// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AnimInstances/WWAnimInstance.h"

#include "GameplayTagContainer.h"
#include "Common/WWBlueprintFunctionLibrary.h"

bool UWWAnimInstance::OwnerHasTag(FGameplayTag Tag) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWWBlueprintFunctionLibrary::NativeActorHasTag(OwningPawn, Tag);
	}

	return false;
}
