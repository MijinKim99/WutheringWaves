// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "Engine/CurveTable.h"
#include "WWStruct.generated.h"

class APlayerWeapon;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponStatData : public FTableRowBase
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StatName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StatSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StatNum;
};

USTRUCT(BlueprintType)
struct FWeaponSkillData : public FTableRowBase
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillRank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeaponStatData> SkillStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveTable* SkillCurve;
};

USTRUCT(BlueprintType)
struct FItemBase : public FTableRowBase
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FString Index;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UTexture2D* Image;
};

USTRUCT(BlueprintType)
struct FWeaponData : public FItemBase
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Weapon")
	APlayerWeapon* WeaponActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(Categories="Player.Weapon"))
	FGameplayTag WeaponTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 WeaponLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	int32 WeaponRank;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 WeaponSkillRank;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FWeaponStatData> WeaponStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FWeaponSkillData> WeaponSkills;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FString WeaponDescription;
};

//TODO::Echo랑 Consume Item 구조체 추가하기

// 아이템 배열을 포함한 인벤토리 구조체
USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_BODY()

public:
	// 여러 아이템을 저장할 수 있는 배열 (포인터 사용 없이 값으로 처리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemBase> Items;

	// 아이템 추가 함수
	void AddItem(const FItemBase& NewItem)
	{
		Items.Add(NewItem);  // 아이템을 배열에 추가
	}
	
};