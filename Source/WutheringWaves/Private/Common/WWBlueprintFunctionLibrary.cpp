// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/WWBlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"


void UWWBlueprintFunctionLibrary::AddTagToActor(AActor* Actor, FGameplayTag Tag)
{
	
}

void UWWBlueprintFunctionLibrary::RemoveTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	
}

bool UWWBlueprintFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	/*
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	return ASC->HasMatchingGameplayTag(Tag);
	*/
	return false;
}

bool UWWBlueprintFunctionLibrary::IstargetPawnHostile(APawn* OwningPawn, APawn* TagetPawn)
{
	check(OwningPawn && TagetPawn);

	IGenericTeamAgentInterface* OwningTeamAgent = Cast<IGenericTeamAgentInterface>(OwningPawn->GetController());
	IGenericTeamAgentInterface* TagetTeamAgent = Cast<IGenericTeamAgentInterface>(TagetPawn->GetController());

	if (OwningTeamAgent && TagetTeamAgent)
	{
		return OwningTeamAgent->GetGenericTeamId() != TagetTeamAgent->GetGenericTeamId();
	}

	return false;
}