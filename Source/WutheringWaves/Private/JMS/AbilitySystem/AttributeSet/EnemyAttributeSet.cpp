// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AbilitySystem/AttributeSet/EnemyAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWGameplayTags.h"
#include "Common/Components/WWHUDSharedUIComponent.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "Common/Interfaces/WWHUDSharedUIInterface.h"
#include "KMJ/UIComponents/PawnUIComponent.h"


UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitPhysicalResistance(1.f);
	InitIceResistance(1.f);
	InitFireResistance(1.f);
	InitLightningResistance(1.f);
	InitWindResistance(1.f);
	InitLightningResistance(1.f);
	InitDarkResistance(1.f);
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (UWWBlueprintFunctionLibrary::NativeActorHasTag(Data.Target.GetOwnerActor(),WWGameplayTags::Shared_Status_Dead))
	{
		return;
	}
	if (!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	// if (!CachedHUDSharedUIInterface.IsValid())
	// {
	// 	CachedHUDSharedUIInterface = TWeakInterfacePtr<IWWHUDSharedUIInterface>(Data.Target.GetAvatarActor());
	// }
	checkf(CachedUIInterface.IsValid(), TEXT("%s does not Implementation IPawnUIInterface."),
	       *Data.Target.GetAvatarActor()->GetActorLabel());
	// checkf(CachedHUDSharedUIInterface.IsValid(), TEXT("%s does not Implementation IWWHUDSharedUIInterface."),
	//        *Data.Target.GetAvatarActor()->GetActorLabel());
	UPawnUIComponent* PawnUIComponent = CachedUIInterface->GetPawnUIComponent();
	// UWWHUDSharedUIComponent* HUDSharedUIComponent = CachedHUDSharedUIInterface->GetHUDSharedUIComponent();

	checkf(PawnUIComponent, TEXT("Can not Load PawnUIComponent from %s"),
	       *Data.Target.GetAvatarActor()->GetActorLabel());
	// checkf(HUDSharedUIComponent, TEXT("Can not Load WWHUDSharedUIComponent from %s"),
	//        *Data.Target.GetAvatarActor()->GetActorLabel());
	//
	// if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	// {
	// 	const float NewCurrentHp = FMath::Clamp(GetCurrentHp(), 0.0f, GetMaxHp());
	// 	SetCurrentHp(NewCurrentHp);
	//
	// 	PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp()/GetMaxHp());
	// }
	//
	// if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	// {
	// 	const float BeforeHp = GetCurrentHp();
	// 	const float Damage = GetDamageTaken();
	//
	// 	const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.0f, GetMaxHp());
	// 	SetCurrentHp(NewCurrentHp);
	//
	// 	const FString DebugString =
	// 		FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
	//
	// 	Debug::Print(DebugString, FColor::Green);
	// 	
	// 	
	// 	PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp()/GetMaxHp());
	//
	// 	//Character Death Process
	// 	if (NewCurrentHp == 0.0f)
	// 	{
	// 		UWWBlueprintFunctionLibrary::AddTagToActor(Data.Target.GetAvatarActor(), WWGameplayTags::Shared_Status_Dead);
	// 	}
	// }
}
