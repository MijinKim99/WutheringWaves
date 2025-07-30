// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/BlueprintAsyncAction/ActivateAbilityAndWaitForEnd.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "Common/WWDebugHelper.h"
#include "Engine/RendererSettings.h"

UActivateAbilityAndWaitForEnd* UActivateAbilityAndWaitForEnd::ActivateAbilityAndWaitForEnd(
	UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& AbilityTag)
{
	UActivateAbilityAndWaitForEnd* Node = NewObject<UActivateAbilityAndWaitForEnd>();

	Node->ASC = AbilitySystemComponent;
	Node->AbilityTag = AbilityTag;
	return Node;
}

void UActivateAbilityAndWaitForEnd::Activate()
{
	check(AbilityTag.IsValid()&&ASC);

	TArray<FGameplayAbilitySpec*> AbilitySpecs;

	//이 함수는 활성화 가능한 모든 게임어빌리티 스팩을 가져온다.
	ASC->GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTag.GetSingleTagContainer(), AbilitySpecs);

	// Debug::Print(TEXT("Check Here"));
	//AbilitySpecs 배열에 받은 데이터가 유효하면
	if (!AbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

		check(AbilitySpec);

		if (!AbilitySpec->IsActive())
		{
			if (ASC->TryActivateAbility(AbilitySpec->Handle))
			{
				UGameplayAbility* Ability = AbilitySpec->GetPrimaryInstance();
				if (Ability)
				{
					Ability->OnGameplayAbilityEnded.AddUObject(
						this, &UActivateAbilityAndWaitForEnd::BroadCastOnAbilityEnd);

					Ability->OnGameplayAbilityCancelled.AddUObject(
						this, &UActivateAbilityAndWaitForEnd::BroadCastOnAbilityCancelled);
				}
				else
				{
					OnAbilityCancelled.Broadcast();
				}
			}
			else
			{
				BroadCastOnAbilityEnd(AbilitySpec->Ability);
				//Debug::Print(FString::Printf(TEXT("%s : Ability Activation Failed"), *AbilitySpec->Ability->GetName()));
			}
		}
	}
}

void UActivateAbilityAndWaitForEnd::BroadCastOnAbilityEnd(UGameplayAbility* Ability)
{
	OnAbilityEnd.Broadcast();
	// Debug::Print(FString::Printf(TEXT("%s : Ability End"), *Ability->GetName()));
}

void UActivateAbilityAndWaitForEnd::BroadCastOnAbilityCancelled()
{
	OnAbilityCancelled.Broadcast();
}
