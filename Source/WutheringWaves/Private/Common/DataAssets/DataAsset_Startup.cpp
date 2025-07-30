// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/DataAssets/DataAsset_Startup.h"

#include "Common/WWDebugHelper.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "Common/AbilitySystem/Abilities/WWGameplayAbility.h"

void UDataAsset_Startup::GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level)
{
	//ASC정보가 유효한지 체크  
	if (!ASC)
	{
		//Debug::Print(TEXT("DataAsset_Startup : can't find ASC"));
	}

	//두 종류 모두 부여
	GrantAbilities(ActivateOnGivenAbilities, ASC, Level);
	GrantAbilities(ReactiveAbilities, ASC, Level);

	if (!StartupGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& BP_Effect : StartupGameplayEffects)
		{
			if (!BP_Effect) continue;

			//BP클래스에서 순수 c++클래스를 추출해서 사용
			UGameplayEffect* EffectCDO = BP_Effect->GetDefaultObject<UGameplayEffect>();
			ASC->ApplyGameplayEffectToSelf(EffectCDO, Level, ASC->MakeEffectContext());
		}
	}
}

void UDataAsset_Startup::GrantAbilities(const TArray<TSubclassOf<UWWGameplayAbility>> GAs, UWWAbilitySystemComponent* InASC, int32 Level)
{
	//게임플레이어빌리티가 없으면 탈출
	if (GAs.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWWGameplayAbility> Ability : GAs)
	{
		//게임플레이 스펙을 만들어서 데이터 주입
		FGameplayAbilitySpec Spec(Ability);
		Spec.SourceObject = InASC->GetAvatarActor();
		Spec.Level = Level;

		//주입된 스펙을 사용할 어빌리티 시스템 컴포넌트에 전달
		InASC->GiveAbility(Spec);
	}
}