// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_StartupBase.h"

#include "GameplayEffect.h"
#include "AbilitySystem/WWAbilitySystemComponent.h"

void UDataAsset_StartupBase::GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level)
{
	//ASC정보가 유효한지 체크
	check(ASC);


	if (!StartupGameplayEffects.IsEmpty())
	{
		for ( const TSubclassOf<UGameplayEffect>& BP_GameplayEffect : StartupGameplayEffects)
		{
			if (!BP_GameplayEffect) continue;

			//BP클래스에서 Native c++클래스를 추출해서 사용
			UGameplayEffect* EffectCDO = BP_GameplayEffect->GetDefaultObject<UGameplayEffect>();
			ASC->ApplyGameplayEffectToSelf(EffectCDO, Level, ASC->MakeEffectContext());
		}
	}
}
