// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Widget/WWUserWidget.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "Common/Interfaces/WWHUDSharedUIInterface.h"
#include "KMJ/UIComponents/PlayerUIComponent.h"
#include "KMJ/UIComponents/EnemyUIComponent.h"

void UWWUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UWWUserWidget::InitEnemyCreateWidget(AActor* EnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(EnemyActor))
	{
		if (UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}

void UWWUserWidget::InitPlayerCreateWidget(AActor* PlayerCharacter)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(PlayerCharacter))
	{
		if (UPawnUIComponent* PawnUIComponent = PawnUIInterface->GetPawnUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PawnUIComponent);
		}
	}
}

void UWWUserWidget::InitHUDSharedWidget(AActor* UIOwner)
{
	if (IWWHUDSharedUIInterface* HUDSharedUIInterface = Cast<IWWHUDSharedUIInterface>(UIOwner))
	{
		if (UWWHUDSharedUIComponent* HUDSharedUIComponent = HUDSharedUIInterface->GetHUDSharedUIComponent())
		{
			BP_OnOwningHUDSharedUIComponentInitialized(HUDSharedUIComponent);
		}
	}
}
