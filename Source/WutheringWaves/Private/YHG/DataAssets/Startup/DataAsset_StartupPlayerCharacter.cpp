// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/DataAssets/Startup/DataAsset_StartupPlayerCharacter.h"
#include "Common/AbilitySystem/Abilities/WWGameplayAbility.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"

bool FPlayerInputAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_StartupPlayerCharacter::GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(ASC, Level);

	for(const FPlayerInputAbilitySet& AbilitySet : PlayerStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;
        
		FGameplayAbilitySpec Spec(AbilitySet.AbilityToGrant);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		//동적태그 생성 
		Spec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		ASC->GiveAbility(Spec);
	}
}