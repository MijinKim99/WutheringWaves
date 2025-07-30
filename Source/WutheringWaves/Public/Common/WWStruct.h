// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "WWDebugHelper.h"
#include "WWEnum.h"
#include "Engine/CurveTable.h"
#include "WWStruct.generated.h"

class AWWWeaponBase;
enum class EItemType : uint8;
enum class EWeaponRarity : uint8;
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
	EWeaponStatType StatName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatSign StatSign;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillStack;
	
	FString GetFormattedDescription() const
	{
		FString Result = SkillDescription;

		for (int32 i = 0; i < SkillStats.Num(); ++i)
		{
			FString StatNameKey = FString::Printf(TEXT("{StatName%d}"), i + 1);
			FString StatNumKey  = FString::Printf(TEXT("{StatNum%d}"), i + 1);

			// StatName 매핑
			FString EnumName = UEnum::GetDisplayValueAsText(SkillStats[i].StatName).ToString();
			FString StatName;

			// CurveTable에서 실시간으로 StatNum 가져오기
			float StatNumFloat = 0.f;
			
			if (!SkillCurve) StatNumFloat = 0.0f;
			// 올바른 RowName 생성 (예: "Attack")
			FName RowName = FName(*EnumName);
			FRealCurve* Curve = SkillCurve->FindCurve(RowName, TEXT("WeaponSkillInit"));

			if (Curve)
			{
				float StatNum = Curve->Eval(static_cast<float>(SkillRank));
				//Debug::Print(FString::Printf(TEXT("StatNum: %f"), StatNum));
				StatNumFloat = StatNum;
			}
			
			if (EnumName == "Attack")
				StatName = TEXT("공격력");
			else if (EnumName == "Critical Percent")
				StatName = TEXT("크리티컬");
			else if (EnumName == "Energy Regen")
				StatName = TEXT("공명 효율");
			else if (EnumName == "Basic ATK")
				StatName = TEXT("일반 공격 피해 보너스");
			else
				StatName = EnumName;

			FString StatNum = FString::SanitizeFloat(StatNumFloat, 1);
			if (SkillStats[i].StatSign == EStatSign::Multiple) StatNum += TEXT("%");

			Result = Result.Replace(*StatNameKey, *StatName);
			Result = Result.Replace(*StatNumKey, *StatNum);
		}
		
		// 추가 치환: 스택 수, 지속 시간 등
		Result = Result.Replace(TEXT("{SkillStack}"), *FString::FromInt(SkillStack));
		Result = Result.Replace(TEXT("{SkillTime}"), *FString::SanitizeFloat(SkillTime,
			1));

		return Result;
	}
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

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	EItemType ItemType;

	EItemType GetItemType() const { return ItemType; }
};

USTRUCT(BlueprintType)
struct FWeaponData : public FItemBase
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWWWeaponBase> WeaponActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(Categories="Player.Weapon"),Category = "Weapon")
	FGameplayTag WeaponTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Weapon")
	EItemRarity WeaponRarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 WeaponLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	int32 WeaponRank;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	TArray<FWeaponStatData> WeaponStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	FWeaponSkillData WeaponSkills;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FString WeaponDescription;
};

//TODO::Echo랑 Consume Item 구조체 추가하기

// 아이템 배열을 포함한 인벤토리 구조체
USTRUCT(BlueprintType)
struct FInventory_Base : public FTableRowBase
{
	GENERATED_BODY()

public:
	//아이템 불러오기 위한 용도의 아이템 원래의 인덱스 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString RowIndex;
	
};

USTRUCT(BlueprintType)
struct FInventory_Weapon : public FInventory_Base
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory_Weapon")
	int32 WeaponCurrentLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory_Weapon")
	int32 WeaponCurrentRank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillRank;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory_Weapon")
	ECharacterName ItemOwner;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory_Weapon")
	UTexture2D* ItemOwnerImage;
};