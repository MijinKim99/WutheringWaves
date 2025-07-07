#pragma once

UENUM()
enum class EWWConfirmType : uint8
{
	Yes,
	No,
};

UENUM()
enum class EWWValidType : uint8
{
	Valid,
	InValid
};

UENUM()
enum class EWWSuccessType : uint8
{
	Success,
	Failed,
};

//0703 KMJ Add_Weapon & WeaponSkill & Inventory 관련
UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	FiveStar,
	FourStar,
	ThreeStar,
	TwoStar,
	OneStar
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Echo,
	Consume
};

UENUM(BlueprintType)
enum class EWeaponStatType : uint8
{
	Attack,
	CriticalPercent,
	EnergyRegen,
	BasicATK
};

UENUM()
enum class EStatSign : uint8
{
	Plus,
	Multiple
};

UENUM(BlueprintType)
enum class EWeaponLocked : uint8
{
	Locked,
	Unlocked
};

class WWEnum
{
public:
	
};
