// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/PlayerStates/WWPlayerState.h"
#include "Common/WWDebugHelper.h"
#include "YHG/AbilitySystem/PlayerAttributeSet.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

AWWPlayerState::AWWPlayerState()
{
	WWAbilitySystemComponent = CreateDefaultSubobject<UWWAbilitySystemComponent>("WWAbilitySystemComponent");
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

void AWWPlayerState::BeginPlay()
{
	Super::BeginPlay();
	OnPawnSet.AddUniqueDynamic(this, &ThisClass::ChangedPlayerCharacter);
}

void AWWPlayerState::ChangedPlayerCharacter(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	if (APlayerCharacter* OldPlayerCharacter =Cast<APlayerCharacter>(OldPawn))
	{
		WWAbilitySystemComponent->RemoveSpawnedAttribute(OldPlayerCharacter->GetResonatorAttributeSet());
	}
	WWAbilitySystemComponent->InitAbilityActorInfo(this, NewPawn);
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(NewPawn);
	if (PlayerCharacter)
	{
		WWAbilitySystemComponent->AddSpawnedAttribute(PlayerCharacter->GetResonatorAttributeSet());
	}
}

UAbilitySystemComponent* AWWPlayerState::GetAbilitySystemComponent() const
{
	return WWAbilitySystemComponent;
}


void AWWPlayerState::CancelPlayerActiveAbilities(UAbilitySystemComponent* ASC, FGameplayTag CancelTag)
{
	if (!ASC || !CancelTag.IsValid())
	{
		Debug::Print(TEXT("WWPlayerState : CancelPlayerActiveAbilities, Can't find ASC or CancelTag"));
		return;
	}

	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (!Spec.IsActive())
			continue;

		const UGameplayAbility* AbilityCDO = Spec.Ability;
		if (!AbilityCDO)
			continue;

		// 어빌리티에 태그가 포함되어 있으면
		if (AbilityCDO->AbilityTags.HasTagExact(CancelTag))
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}

void AWWPlayerState::CancelAllPlayerActiveAbilities(UAbilitySystemComponent* ASC)
{
	if (!ASC)
	{
		Debug::Print(TEXT("WWPlayerState : CancelAllActiveAbilities, Can't find ASC"));
		return;
	}

	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (Spec.IsActive())
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}
