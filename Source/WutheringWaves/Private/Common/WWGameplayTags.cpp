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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_LightRover, "InputTag.LightAttack.LightRover")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Chixia, "InputTag.LightAttack.Chixia")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Verina, "InputTag.LightAttack.Verina")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill, "InputTag.LightAttack")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_LightRover, "InputTag.Skill.LightRover")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_Chixia, "InputTag.Skill.Chixia")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_Verina, "InputTag.Skill.Verina")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Burst, "InputTag.Burst")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Burst_LightRover, "InputTag.Burst.LightRover")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Burst_Chixia, "InputTag.Burst.Chixia")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Burst_Verina, "InputTag.Burst.Verina")
	
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
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitEnemy, "Player.Event.HitEnemy")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_DashHit, "Player.Event.DashHit")
	

	//Player Ability
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dash, "Player.Ability.Dash")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_LightAttack, "Player.Ability.LightAttack")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill, "Player.Ability.Skill")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Burst, "Player.Ability.Burst")

	//Player Status
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_PlayingCharacter, "Player.Status.PlayingCharacter")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_PlayingCharacter_LightRover, "Player.Status.PlayingCharacter.LightRover")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_PlayingCharacter_Chixia, "Player.Status.PlayingCharacter.Chixia")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_PlayingCharacter_Verina, "Player.Status.PlayingCharacter.Verina")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dashing, "Player.Status.Dashing")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jumping, "Player.Status.Jumping")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_LightAttacking, "Player.Status.LightAttacking")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_UseSkill, "Player.Status.UseSkill")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SkillCoolTime, "Player.Status.SkillCoolTime")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SkillCoolTime_LightRover, "Player.Status.SkillCoolTime.LightRover")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SkillCoolTime_Chixia, "Player.Status.SkillCoolTime.Chixia")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_SkillCoolTime_Verina, "Player.Status.SkillCoolTime.Verina")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_UseBurst, "Player.Status.UseBurst")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_BurstCoolTime, "Player.Status.BurstCoolTime")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_BurstCoolTime_LightRover, "Player.Status.BurstCoolTime.LightRover")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_BurstCoolTime_Chixia, "Player.Status.BurstCoolTime.Chixia")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_BurstCoolTime_Verina, "Player.Status.BurstCoolTime.Verina")

	//Shared SetByCaller
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Physical, "Shared.SetByCaller.Damage.Physical")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Ice, "Shared.SetByCaller.Damage.Ice")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Fire, "Shared.SetByCaller.Damage.Fire")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Lightning, "Shared.SetByCaller.Damage.Lightning")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Wind, "Shared.SetByCaller.Damage.Wind")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Light, "Shared.SetByCaller.Damage.Light")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Dark, "Shared.SetByCaller.Damage.Dark")
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Stagger, "Shared.SetByCaller.Damage.Stagger")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage_Parry, "Shared.SetByCaller.Damage.Parry")

	//Shared Status
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Hit_Falling, "Shared.Status.Hit.Falling")

	//Shared Event
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Small, "Shared.Event.HitReact.Small")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Big, "Shared.Event.HitReact.Big")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Pushed, "Shared.Event.HitReact.Pushed")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Animation_LoopEnd, "Shared.Event.HitReact.LoopEnd")

	//Shared Ability
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact_Small, "Shared.Ability.HitReact.Small")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact_Big, "Shared.Ability.HitReact.Big")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact_Pushed, "Shared.Ability.HitReact.Pushed")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death")

	//Enemy Ability
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Start, "Enemy.Ability.Start")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack_Melee, "Enemy.Ability.Attack.Melee")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack_Moving, "Enemy.Ability.Attack.Moving")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack_Ranged, "Enemy.Ability.Attack.Ranged")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_StepBack, "Enemy.Ability.StepBack")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Staggered, "Enemy.Ability.Staggered")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Parried, "Enemy.Ability.Parried")

	//Enemy Event
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_HitStart, "Enemy.Event.HitStart")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_HitEnd, "Enemy.Event.HitEnd")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_Parried, "Enemy.Event.Parried")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_Start, "Enemy.Event.Start")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_Death, "Enemy.Event.Death")
	

	//Enemy Status
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Staggered, "Enemy.Status.Staggered")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_ParryEnabled, "Enemy.Status.ParryEnabled")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_HitCooldown, "Enemy.Status.HitCooldown")

	//JMS Test Player Event
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitEnemy_Start, "Player.Event.HitEnemy.Start")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitEnemy_End, "Player.Event.HitEnemy.End")
	
}
