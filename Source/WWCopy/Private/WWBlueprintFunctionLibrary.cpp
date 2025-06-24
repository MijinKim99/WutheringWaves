// Fill out your copyright notice in the Description page of Project Settings.


#include "WWBlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WWAbilitySystemComponent.h"


UWWAbilitySystemComponent* UWWBlueprintFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);
	return CastChecked<UWWAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UWWBlueprintFunctionLibrary::AddTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UWWAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->AddLooseGameplayTag(Tag);
	}
}

void UWWBlueprintFunctionLibrary::RemoveTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UWWAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->RemoveLooseGameplayTag(Tag);
	}
}

bool UWWBlueprintFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	return NativeGetAbilitySystemComponentFromActor(Actor)->HasMatchingGameplayTag(Tag);
}

void UWWBlueprintFunctionLibrary::BP_HasTag(AActor* Actor, FGameplayTag Tag, EWWConfirmType& OutType)
{
	OutType = NativeActorHasTag(Actor, Tag) ? EWWConfirmType::Yes : EWWConfirmType::No;
}
