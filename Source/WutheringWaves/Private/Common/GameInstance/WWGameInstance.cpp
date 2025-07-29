// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/GameInstance/WWGameInstance.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "JMS/TowerBattleSystem/WWTowerBattlePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "YHG/AbilitySystem/PlayerStateAttributeSet.h"

TSubclassOf<AWWTowerBattlePlayer> UWWGameInstance::GetCurrentTowerBattlePlayerClass()
{
	return CurrentTowerBattlePlayerClass;
}

void UWWGameInstance::SetCurrentTowerBattlePlayerClass(TSubclassOf<AWWTowerBattlePlayer> TowerBattlePlayerClass)
{
	CurrentTowerBattlePlayerClass = TowerBattlePlayerClass;
}

void UWWGameInstance::RegisterReferencedObject(UObject* ObjectToReference)
{
	Super::RegisterReferencedObject(ObjectToReference);
}
