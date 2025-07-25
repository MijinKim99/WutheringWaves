// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WWGameInstance.generated.h"

class AWWTowerBattlePlayer;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, Category = "TowerBattle")
	TSubclassOf<AWWTowerBattlePlayer> CurrentTowerBattlePlayerClass;
public:
	UFUNCTION(BlueprintCallable, Category = "TowerBattle")
	TSubclassOf<AWWTowerBattlePlayer> GetCurrentTowerBattlePlayerClass();
	UFUNCTION(BlueprintCallable, Category = "TowerBattle")
	void SetCurrentTowerBattlePlayerClass(TSubclassOf<AWWTowerBattlePlayer> TowerBattlePlayerClass);
};
