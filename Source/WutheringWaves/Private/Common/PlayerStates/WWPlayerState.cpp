// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/PlayerStates/WWPlayerState.h"
#include "Common/WWDebugHelper.h"
#include "YHG/AbilitySystem/PlayerStateAttributeSet.h"
#include "YHG/DataAssets/Startup/PlayerCharacterStartup.h"
#include "GameplayAbilitySpec.h"
#include "YHG/AbilitySystem/PlayerCharacterAttributeSet.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

AWWPlayerState::AWWPlayerState()
{
	WWAbilitySystemComponent = CreateDefaultSubobject<UWWAbilitySystemComponent>("WWAbilitySystemComponent");
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerStateAttributeSet>(TEXT("PlayerAttributeSet"));
}

void AWWPlayerState::BeginPlay()
{
	Super::BeginPlay();

	OnPawnSet.AddDynamic(this, &ThisClass::ChangedPlayerCharacter);

	//초기설정
	WWAbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		WWAbilitySystemComponent->AddSpawnedAttribute(PlayerCharacter->GetPlayerCharacterAttributeSet());
	}

	//교안 DA_ApplYEffecttoSelf

	//DataAsset으로 어빌리티 부여
	if (CommonStartupData.IsNull())
	{
		Debug::Print(TEXT("WWPlayerState : Can't find StartupData"));
		return;
	}
	else
	{
		if (UPlayerCharacterStartup* LoadedData = CommonStartupData.LoadSynchronous())
		{
			//Startup데이터가 Null이 아닌경우 StartupData는 동기화로드를 거쳐서 최종적으로 게임어빌리티시스템이 발동된다. 
			LoadedData->GiveToAbilitySystemComponent(WWAbilitySystemComponent);
		}
	}
	//여기다 for문 돌려서 다른 캐릭터들 능력 전부 부여
	for (TSoftObjectPtr<UPlayerCharacterStartup> PlayerCharacterStartup : CharacterStartupData)
	{
		if (PlayerCharacterStartup.IsNull())
		{
			Debug::Print(TEXT("WWPlayerState : Can't find StartupData"));
			return;
		}
		else
		{
			if (UPlayerCharacterStartup* LoadedData = PlayerCharacterStartup.LoadSynchronous())
			{
				//Startup데이터가 Null이 아닌경우 StartupData는 동기화로드를 거쳐서 최종적으로 게임어빌리티시스템이 발동된다. 
				LoadedData->GiveToAbilitySystemComponent(WWAbilitySystemComponent);
			}
		}
	}
}

void AWWPlayerState::ChangedPlayerCharacter(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	// if (!IsValid(NewPawn) || !IsValid(OldPawn))
	// {
	// 	Debug::Print(TEXT("WWPlayerState : InValid NewPawn or OldPawn"));
	// 	return;
	// }

	Debug::Print(TEXT("AWWPlayerState::ChangedPlayerCharacter"));
	if (APlayerCharacter* OldPlayerCharacter = Cast<APlayerCharacter>(OldPawn))
	{
		WWAbilitySystemComponent->RemoveSpawnedAttribute(OldPlayerCharacter->GetPlayerCharacterAttributeSet());
	}
	//WWAbilitySystemComponent->SetAvatarActor(NewPawn);

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(NewPawn))
	{
		WWAbilitySystemComponent->AddSpawnedAttribute(PlayerCharacter->GetPlayerCharacterAttributeSet());
		WWAbilitySystemComponent->InitAbilityActorInfo(this, PlayerCharacter);
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
	FScopedAbilityListLock ActiveScopeLock(*GetAbilitySystemComponent());
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
