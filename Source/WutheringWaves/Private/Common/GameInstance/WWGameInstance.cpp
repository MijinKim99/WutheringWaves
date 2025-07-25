// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/GameInstance/WWGameInstance.h"

#include "JMS/TowerBattleSystem/WWTowerBattlePlayer.h"

TSubclassOf<AWWTowerBattlePlayer> UWWGameInstance::GetCurrentTowerBattlePlayerClass()
{
	return CurrentTowerBattlePlayerClass;
}

void UWWGameInstance::SetCurrentTowerBattlePlayerClass(TSubclassOf<AWWTowerBattlePlayer> TowerBattlePlayerClass)
{
	CurrentTowerBattlePlayerClass = TowerBattlePlayerClass;
}
