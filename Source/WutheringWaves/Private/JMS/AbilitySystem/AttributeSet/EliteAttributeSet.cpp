// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AbilitySystem/AttributeSet/EliteAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "KMJ/UIComponents/PawnUIComponent.h"


UEliteAttributeSet::UEliteAttributeSet()
{
	InitCurrentStagger(1.f);
	InitMaxStagger(1.f);
	InitStaggerDamageTaken(1.f);
}

void UEliteAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedUIInterface.IsValid(), TEXT("%s does not Implementation IPawnUIInterface."),
	       *Data.Target.GetAvatarActor()->GetActorLabel());

	UPawnUIComponent* PawnUIComponent = CachedUIInterface->GetPawnUIComponent();


	checkf(PawnUIComponent, TEXT("Can not Load PawnUIComponent from %s"),
	       *Data.Target.GetAvatarActor()->GetActorLabel());
	if (Data.EvaluatedData.Attribute == GetCurrentStaggerAttribute())
	{
		const float NewCurrentStagger = FMath::Clamp(GetCurrentStagger(), 0.0f, GetMaxStagger());
		SetCurrentStagger(NewCurrentStagger);

		//공진 UI 업데이트
		// PawnUIComponent->OnCurrentStaggerChanged.Broadcast(GetCurrentStagger()/GetMaxStagger());
	}
	if (Data.EvaluatedData.Attribute == GetStaggerDamageTakenAttribute())
	{
		const float BeforeStagger = GetCurrentStagger();
		const float StaggerDamage = GetStaggerDamageTaken();
		const float NewCurrentStagger = FMath::Clamp(BeforeStagger - StaggerDamage, 0.0f, GetMaxStagger());
		SetCurrentStagger(NewCurrentStagger);
		const FString DebugString =
			FString::Printf(
				TEXT("Before Stagger: %f, Stagger Damage: %f, NewCurrentStagger : %f"), BeforeStagger, StaggerDamage,
				NewCurrentStagger);
		Debug::Print(DebugString, FColor::Green);
		//공진 UI 업데이트
		// PawnUIComponent->OnCurrentStaggerChanged.Broadcast(GetCurrentStagger()/GetMaxStagger());
		if (NewCurrentStagger == 0.0f)
		{
			UWWBlueprintFunctionLibrary::AddTagToActor(Data.Target.GetAvatarActor(),WWGameplayTags::Enemy_Status_Staggered);
		}
	}
	if (Data.EvaluatedData.Attribute == GetParryDamageTakenAttribute())
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(),
																 WWGameplayTags::Enemy_Event_Parried,
																 FGameplayEventData());
		const float ParryDamage = GetParryDamageTaken();
		const float BeforeStagger = GetCurrentStagger();
		const float NewCurrentStagger = FMath::Clamp(BeforeStagger - ParryDamage, 0.0f, GetMaxStagger());
		SetCurrentStagger(NewCurrentStagger);
		const FString DebugString =
			FString::Printf(
				TEXT("Before Stagger: %f, Parry Damage: %f, NewCurrentStagger : %f"), BeforeStagger, ParryDamage,
				NewCurrentStagger);
		Debug::Print(DebugString, FColor::Green);
		//공진 UI 업데이트
		// PawnUIComponent->OnCurrentStaggerChanged.Broadcast(GetCurrentStagger()/GetMaxStagger());
		if (NewCurrentStagger == 0.0f)
		{
			UWWBlueprintFunctionLibrary::AddTagToActor(Data.Target.GetAvatarActor(),WWGameplayTags::Enemy_Status_Staggered);
		}
	}
}
