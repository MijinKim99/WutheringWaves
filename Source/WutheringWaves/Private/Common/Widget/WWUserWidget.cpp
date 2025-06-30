// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Widget/WWUserWidget.h"

#include "Common/Interfaces/WWInterface.h"
#include "KMJ/UIComponents/PlayerUIComponent.h"
#include "KMJ/UIComponents/EnemyUIComponent.h"

void UWWUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (IWWInterface* PawnUIInterface = Cast<IWWInterface>(GetOwningPlayerPawn()))
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UWWUserWidget::InitEnemyCreateWidget(AActor* EnemyActor)
{
	if (IWWInterface* PawnUIInterface = Cast<IWWInterface>(EnemyActor))
	{
		if (UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}
