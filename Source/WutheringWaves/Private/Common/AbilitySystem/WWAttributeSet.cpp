// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AbilitySystem/WWAttributeSet.h"
#include "Common/WWDebugHelper.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "GameplayEffectExtension.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWGameplayTags.h"
#include "KMJ/UIComponents/PawnUIComponent.h"

UWWAttributeSet::UWWAttributeSet()
{
	InitCurrentHp(1.f);
	InitMaxHp(1.f);
	
	InitApplyAttack(1.f);
	InitBasicAttack(1.f);
	
	InitApplyDefense(1.f);
	InitBasicDefense(1.f);
	
	InitDamageTaken(1.f);
}

void UWWAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (!CachedUIInterface.IsValid())
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
	
	checkf(PawnUIComponent, TEXT("Can not Load PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorLabel());
	
	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		const float NewCurrentHp = FMath::Clamp(GetCurrentHp(), 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);

		PawnUIComponent->OnCurrentHpValueChanged.Broadcast(GetCurrentHp(), GetMaxHp());
		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp()/GetMaxHp());
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeHp = GetCurrentHp();
		const float Damage = GetDamageTaken();

		const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);

		//const FString DebugString =
			//FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);

		//Debug::Print(DebugString, FColor::Green);
		
		PawnUIComponent->OnCurrentHpValueChanged.Broadcast(GetCurrentHp(), GetMaxHp());
		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp()/GetMaxHp());

		//Character Death Process
		if (NewCurrentHp == 0.0f)
		{
			UWWBlueprintFunctionLibrary::AddTagToActor(Data.Target.GetAvatarActor(), WWGameplayTags::Shared_Status_Dead);
		}
	}
}