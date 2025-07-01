// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/WWGameplayTags.h"

namespace WWGameplayTags
{
	//Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dash, "InputTag.Dash")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Hold, "InputTag.Hold")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle, "InputTag.Toggle")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle_Targeting, "InputTag.Toggle.Targeting")
	
	//Player Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Swords, "Player.Weapon.Swords")
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Pistols, "Player.Weapon.Pistols")
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rectifiers, "Player.Weapon.Rectifiers")

	//Event
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_WeaponEquip, "Player.Event.WeaponEquip")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_WeaponUnEquip, "Player.Event.WeaponUnEquip")

	//Ability
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dash, "Player.Ability.Dash")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump")
	/*UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Swords, "Player.Ability.Equip.Swords")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Pistols, "Player.Ability.Equip.Pistols")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Rectifiers, "Player.Ability.Equip.Rectifiers")*/

	//Status
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dashing, "Player.Status.Dashing")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jumping, "Player.Status.Jumping")

	//Shared
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage")
}
