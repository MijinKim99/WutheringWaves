// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/WWGameplayTags.h"

namespace WWGameplayTags
{
	//Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dash, "InputTag.Dash")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack, "InputTag.LightAttack")
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Hold, "InputTag.Hold")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle, "InputTag.Toggle")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle_Targeting, "InputTag.Toggle.Targeting")
	
	//Player Weapon
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Swords, "Player.Weapon.Swords")
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Pistols, "Player.Weapon.Pistols")
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rectifiers, "Player.Weapon.Rectifiers")

	//Player Event
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_WeaponEquip, "Player.Event.WeaponEquip")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_WeaponUnEquip, "Player.Event.WeaponUnEquip")

	//Player Ability
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_GroundDash, "Player.Ability.GroundDash")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_AirDash, "Player.Ability.AirDash")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light, "Player.Ability.Attack.Light")

	//Player Status
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dashing, "Player.Status.Dashing")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jumping, "Player.Status.Jumping")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Attacking_Light, "Player.Status.Attacking.Light")

	//Player SetByCaller
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light")

	//Shared
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Physical, "Shared.SetByCaller.Damage.Physical")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Ice, "Shared.SetByCaller.Damage.Ice")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Fire, "Shared.SetByCaller.Damage.Fire")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Lightning, "Shared.SetByCaller.Damage.Lightning")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Wind, "Shared.SetByCaller.Damage.Wind")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Light, "Shared.SetByCaller.Damage.Light")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Dark, "Shared.SetByCaller.Damage.Dark")
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact")

	//Enemy
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack, "Enemy.Ability.Attack")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SpawnHitCollision, "Enemy.Event.SpawnHitCollision")
	
}
