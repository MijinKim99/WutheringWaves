// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AbilitySystem/PlayerCharacterAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Common/WWDebugHelper.h"
#include "GameplayEffectExtension.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWGameplayTags.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "KMJ/UIComponents/PawnUIComponent.h"

UPlayerCharacterAttributeSet::UPlayerCharacterAttributeSet()
{
	InitCurrentHp(1.f);
	InitMaxHp(1.f);

	InitApplyAttack(1.f);
	InitBasicAttack(1.f);

	InitApplyDefense(1.f);
	InitBasicDefense(1.f);

	InitDamageTaken(1.f);

	InitApplyEnergyRegen(1.f);
	InitBasicEnergyRegen(1.f);

	InitApplyCriticalRate(1.f);
	InitBasicCriticalRate(1.f);

	InitApplyCriticalDamage(1.f);
	InitBasicCriticalDamage(1.f);

	InitCurrentSkillCoolTime(1.f);
	InitMaxSkillCoolTime(1.f);

	InitCurrentBurstCoolTime(1.f);
	InitMaxBurstCoolTime(1.f);

	InitCurrentBurstEnergy(1.f);
	InitMaxBurstEnergy(1.f);

	InitCurrentForteCircuitEnergy(1.f);
	InitCurrentForteCircuitEnergy(1.f);

	InitCurrentConcertoEnergy(1.f);
	InitMaxConcertoEnergy(1.f);
	/*
		InitApplyFireDamage(1.f);
		InitBasicFireDamage(1.f);
	
		InitApplyIceDamage(1.f);
		InitBasicIceDamage(1.f);
		
		InitApplyAirDamage(1.f);
		InitBasicAirDamage(1.f);
	
		InitApplyElectricDamage(1.f);
		InitBasicElectricDamage(1.f);
	
		InitApplyLightDamage(1.f);
		InitBasicLightDamage(1.f);
	
		InitApplyDarkDamage(1.f);
		InitBasicDarkDamage(1.f);*/
}

void UPlayerCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedUIInterface.IsValid(), TEXT("%s does not Implementation IPawnUIInterface."),
	       *Data.Target.GetAvatarActor()->GetActorLabel());

	UPawnUIComponent* PawnUIComponent = CachedUIInterface->GetPawnUIComponent();

	//TODO: 플레이어에 UICOmponent 달고 삭제
	if (PawnUIComponent == nullptr)
	{
		return;
	}
	//

	checkf(PawnUIComponent, TEXT("Can not Load PawnUIComponent from %s"),
	       *Data.Target.GetAvatarActor()->GetActorLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		const float NewCurrentHp = FMath::Clamp(GetCurrentHp(), 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);

		PawnUIComponent->OnCurrentHpValueChanged.Broadcast(GetCurrentHp(), GetMaxHp());
		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp() / GetMaxHp());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentBurstEnergyAttribute())
	{
		//Debug::Print(TEXT("BurstEnergyAttribute is now %f"), GetCurrentBurstEnergy());
		if (GetCurrentBurstEnergy() > GetMaxBurstEnergy())
		{
			SetCurrentBurstEnergy(GetMaxBurstEnergy());
		}
		PawnUIComponent->OnCurrentBurstEnergyChanged.Broadcast(GetCurrentBurstEnergy() / GetMaxBurstEnergy());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentForteCircuitEnergyAttribute())
	{
		if (GetCurrentForteCircuitEnergy() > GetMaxForteCircuitEnergy())
		{
			SetCurrentForteCircuitEnergy(GetMaxForteCircuitEnergy());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		if (UWWBlueprintFunctionLibrary::NativeActorHasTag(Data.Target.GetAvatarActor(),
		                                                   WWGameplayTags::Player_Status_Dashing))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(),
			                                                         WWGameplayTags::Player_Event_DashHit,
			                                                         FGameplayEventData());
			return;
		}
		const float BeforeHp = GetCurrentHp();
		const float Damage = GetDamageTaken();

		const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);

		const FString DebugString =
			FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);

		//Debug::Print(DebugString, FColor::Green);

		PawnUIComponent->OnCurrentHpValueChanged.Broadcast(GetCurrentHp(), GetMaxHp());
		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp() / GetMaxHp());

		//Character Death Process
		if (NewCurrentHp == 0.0f)
		{
			UWWBlueprintFunctionLibrary::AddTagToActor(Data.Target.GetAvatarActor(),
			                                           WWGameplayTags::Shared_Status_Dead);
		}
	}
}
