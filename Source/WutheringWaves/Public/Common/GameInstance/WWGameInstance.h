// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "YHG/AbilitySystem/PlayerCharacterAttributeSet.h"
#include "YHG/AbilitySystem/PlayerStateAttributeSet.h"
#include "WWGameInstance.generated.h"

struct FInventory_Weapon;
class UPlayerCharacterAttributeSet;
class UPlayerStateAttributeSet;
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
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "WWGameInstance")
	float SavedRoverHealth;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "WWGameInstance")
	float SavedVerinaHealth;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "WWGameInstance")
	float SavedChixiaHealth;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "WWGameInstance")
	TArray<FInventory_Weapon> SavedInventoryData;
	UFUNCTION(BlueprintCallable, Category = "TowerBattle")
	TSubclassOf<AWWTowerBattlePlayer> GetCurrentTowerBattlePlayerClass();
	UFUNCTION(BlueprintCallable, Category = "TowerBattle")
	void SetCurrentTowerBattlePlayerClass(TSubclassOf<AWWTowerBattlePlayer> TowerBattlePlayerClass);
	UFUNCTION(BlueprintCallable, Category = "WWGameInstance")
	virtual void RegisterReferencedObject(UObject* ObjectToReference) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "WWGameInstance")
	bool bIsSaveDataExist = false;
};
