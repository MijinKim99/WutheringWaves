// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AbilitySystem/AttributeSet/LordAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Common/WWGameplayTags.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "KMJ/UIComponents/PawnUIComponent.h"

void ULordAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
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
}
