// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AbilitySystem/PlayerStateAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "KMJ/UIComponents/PawnUIComponent.h"

UPlayerStateAttributeSet::UPlayerStateAttributeSet()
{
	InitCurrentStamina(1.f);
	InitMaxStamina(1.f);
}

void UPlayerStateAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//UI컴포넌트를 어떻게 해야할까...
	/*if (!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedUIInterface.IsValid(), TEXT("%s does not Implementation IPawnUIInterface."), *Data.Target.GetAvatarActor()->GetActorLabel());
	
	UPawnUIComponent* PawnUIComponent = CachedUIInterface->GetPawnUIComponent();

	//TODO: 플레이어에 UICOmponent 달고 삭제
	if (PawnUIComponent == nullptr)
	{
		return;
	}
	//
	
	checkf(PawnUIComponent, TEXT("Can not Load PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorLabel());*/

	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		if (GetCurrentStamina() > GetMaxStamina())
		{
			SetCurrentStamina(GetMaxStamina());
		}
		
	}
}

float UPlayerStateAttributeSet::GetStaminaPercent()
{
	return GetCurrentStamina()/GetMaxStamina();
}
