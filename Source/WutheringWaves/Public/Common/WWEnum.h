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
UENUM()
enum class EWeaponRarity : uint8
{
	FiveStar,
	FourStar,
	ThreeStar,
	TwoStar,
	OneStar
};

UENUM()
enum class EItemType : uint8
{
	Weapon,
	Echo,
	Consume
};

UENUM()
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

class WWEnum
{
public:
	
};
