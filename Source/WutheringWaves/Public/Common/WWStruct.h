// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
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
	
	void InitializeStats()
	{
		if (!SkillCurve) return;

		for (FWeaponStatData& Stat : SkillStats)
		{
			FName RowName = FName(*UEnum::GetValueAsString(Stat.StatName)); // 예: EWeaponStatType::Attack -> "Attack"
			FRealCurve* Curve = SkillCurve->FindCurve(RowName, TEXT("WeaponSkillInit"));

			if (Curve)
			{
				Stat.StatNum = Curve->Eval(static_cast<float>(SkillRank));
			}
		}
	}
	
	FString GetFormattedDescription() const
	{
		FFormatNamedArguments Args;

		for (int32 i = 0; i < SkillStats.Num(); ++i)
		{
			FString StatNameKey = FString::Printf(TEXT("StatName%d"), i + 1);
			FString StatNumKey = FString::Printf(TEXT("StatNum%d"), i + 1);

			FText StatNameText = UEnum::GetDisplayValueAsText(SkillStats[i].StatName);
			float StatValue = SkillStats[i].StatNum;

			Args.Add(*StatNameKey, StatNameText);
			Args.Add(*StatNumKey, StatValue);
		}
		// SkillDescription이 FString이므로 FText로 변환 후 포맷
		FText FormattedText = FText::Format(FText::FromString(SkillDescription), Args);
		
		return FormattedText.ToString(); // FString으로 반환
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
	EWeaponRarity WeaponRarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 WeaponLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	int32 WeaponRank;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	TArray<FWeaponStatData> WeaponStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	TArray<FWeaponSkillData> WeaponSkills;
	
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
	// 여러 아이템을 저장할 수 있는 배열 (포인터 사용 없이 값으로 처리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString ItemIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	int32 ItemCount;
	
};

USTRUCT(BlueprintType)
struct FInventory_Weapon : public FInventory_Base
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory_Weapon")
	FString ItemOwner;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory_Weapon")
	UTexture2D* ItemOwnerImage;
};