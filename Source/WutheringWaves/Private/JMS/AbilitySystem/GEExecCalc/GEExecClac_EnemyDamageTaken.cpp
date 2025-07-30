// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AbilitySystem/GEExecCalc/GEExecClac_EnemyDamageTaken.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAttributeSet.h"
#include "JMS/AbilitySystem/AttributeSet/EliteAttributeSet.h"
#include "JMS/AbilitySystem/AttributeSet/EnemyAttributeSet.h"
#include "JMS/AbilitySystem/AttributeSet/LordAttributeSet.h"

struct FWWAttributeSetCapture
{
	//BaseAttributeSet에 변수를 캡처
	//DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyAttack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyDefense)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)


	FWWAttributeSetCapture()
	{
		//Source GE - 생성주체, Target GE - 적용대상
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyAttack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyDefense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, DamageTaken, Target, false);
	}
};

static const FWWAttributeSetCapture& GetWWAttributeSetCapture()
{
	static FWWAttributeSetCapture AttributeSetCapture;
	return AttributeSetCapture;
}

struct FEnemyAttributeSetCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(WindResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DarkResistance)

	FEnemyAttributeSetCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, PhysicalResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, IceResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, WindResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, LightResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, DarkResistance, Target, false);
	}
};

static const FEnemyAttributeSetCapture& GetEnemyAttributeSetCapture()
{
	static FEnemyAttributeSetCapture AttributeSetCapture;
	return AttributeSetCapture;
}

struct FEliteAttributeSetCapture
{
	//BaseAttributeSet에 변수를 캡처
	DECLARE_ATTRIBUTE_CAPTUREDEF(StaggerDamageTaken)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ParryDamageTaken)


	FEliteAttributeSetCapture()
	{
		//Source GE - 생성주체, Target GE - 적용대상
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyAttack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEliteAttributeSet, StaggerDamageTaken, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEliteAttributeSet, ParryDamageTaken, Target, false);
	}
};

static const FEliteAttributeSetCapture& GetEliteAttributeSetCapture()
{
	static FEliteAttributeSetCapture AttributeSetCapture;
	return AttributeSetCapture;
}

UGEExecClac_EnemyDamageTaken::UGEExecClac_EnemyDamageTaken()
{
	//RelevantAttributesToCapture 주입
	//RelevantAttributesToCapture.Add(GetDamageCapture().ApplyAttackDef);
	RelevantAttributesToCapture.Add(GetWWAttributeSetCapture().ApplyDefenseDef);
	RelevantAttributesToCapture.Add(GetWWAttributeSetCapture().DamageTakenDef);
	RelevantAttributesToCapture.Add(GetEnemyAttributeSetCapture().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(GetEnemyAttributeSetCapture().IceResistanceDef);
	RelevantAttributesToCapture.Add(GetEnemyAttributeSetCapture().FireResistanceDef);
	RelevantAttributesToCapture.Add(GetEnemyAttributeSetCapture().LightningResistanceDef);
	RelevantAttributesToCapture.Add(GetEnemyAttributeSetCapture().WindResistanceDef);
	RelevantAttributesToCapture.Add(GetEnemyAttributeSetCapture().LightResistanceDef);
	RelevantAttributesToCapture.Add(GetEnemyAttributeSetCapture().DarkResistanceDef);
	RelevantAttributesToCapture.Add(GetEliteAttributeSetCapture().StaggerDamageTakenDef);
	RelevantAttributesToCapture.Add(GetEliteAttributeSetCapture().ParryDamageTakenDef);
}

void UGEExecClac_EnemyDamageTaken::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	// Boilerplate
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	// EnemyAttributeSet에서 Attribute를 불러와서 지역변수에 저장
	float TargetPhysicalResistance = 0.f;
	float TargetIceResistance = 0.f;
	float TargetFireResistance = 0.f;
	float TargetLightningResistance = 0.f;
	float TargetWindResistance = 0.f;
	float TargetLightResistance = 0.f;
	float TargetDarkResistance = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyAttributeSetCapture().PhysicalResistanceDef,
	                                                           EvaluateParameters, TargetPhysicalResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyAttributeSetCapture().IceResistanceDef,
	                                                           EvaluateParameters, TargetIceResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyAttributeSetCapture().FireResistanceDef,
	                                                           EvaluateParameters, TargetFireResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyAttributeSetCapture().LightningResistanceDef,
	                                                           EvaluateParameters, TargetLightningResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyAttributeSetCapture().WindResistanceDef,
	                                                           EvaluateParameters, TargetWindResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyAttributeSetCapture().LightResistanceDef,
	                                                           EvaluateParameters, TargetLightResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyAttributeSetCapture().DarkResistanceDef,
	                                                           EvaluateParameters, TargetDarkResistance);

	// EffectSpec에서 SetByCallerTagMagnitudes를 추출하여 각 태그에 따라 서로 다른 지역변수에 저장
	float SourcePhysicalDamage = 0.f;
	float SourceIceDamage = 0.f;
	float SourceFireDamage = 0.f;
	float SourceLightningDamage = 0.f;
	float SourceWindDamage = 0.f;
	float SourceLightDamage = 0.f;
	float SourceDarkDamage = 0.f;
	float SourceStaggerDamage = 0.f;
	float SourceParryDamage = 0.f;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Physical))
		{
			SourcePhysicalDamage = TagMagnitude.Value;
			SourcePhysicalDamage *= (1.f - TargetPhysicalResistance);
			// Debug::Print(TEXT("PhysicalDamage"), SourcePhysicalDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Ice))
		{
			SourceIceDamage = TagMagnitude.Value;
			SourceIceDamage *= (1.f - TargetIceResistance);
			// Debug::Print(TEXT("IceDamage"), SourceIceDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Fire))
		{
			SourceFireDamage = TagMagnitude.Value;
			// Debug::Print(TEXT("AppliedFireDamage"), SourceFireDamage);
			SourceFireDamage *= (1.f - TargetFireResistance);
			// Debug::Print(TEXT("FireDamage"), SourceFireDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Lightning))
		{
			SourceLightningDamage = TagMagnitude.Value;
			SourceLightningDamage *= (1.f - TargetLightningResistance);
			// Debug::Print(TEXT("LightningDamage"), SourceLightningDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Wind))
		{
			SourceWindDamage = TagMagnitude.Value;
			SourceWindDamage *= (1.f - TargetWindResistance);
			// Debug::Print(TEXT("WindDamage"), SourceWindDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Light))
		{
			SourceLightDamage = TagMagnitude.Value;
			SourceLightDamage *= (1.f - TargetLightResistance);
			// Debug::Print(TEXT("LightDamage"), SourceLightDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Dark))
		{
			SourceDarkDamage = TagMagnitude.Value;
			SourceDarkDamage *= (1.f - TargetDarkResistance);
			// Debug::Print(TEXT("DarkDamage"), SourceDarkDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Stagger))
		{
			SourceStaggerDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("StaggerDamage"), SourceStaggerDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Parry))
		{
			SourceParryDamage = TagMagnitude.Value;
			// Debug::Print(TEXT("StaggerDamage"), SourceStaggerDamage);
		}
	}
	float TargetDefence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWWAttributeSetCapture().ApplyDefenseDef,
	                                                           EvaluateParameters, TargetDefence);
	// Debug::Print(TEXT("TargetDefence"), TargetDefence);

	// 현재는 한번에 하나의 대미지만 들어옴
	float AppliedSourceDamage = SourcePhysicalDamage + SourceIceDamage + SourceFireDamage + SourceLightningDamage +
		SourceWindDamage + SourceLightDamage + SourceDarkDamage;
	// 방어력에 의한 영향 : 1 - (적의 방어력/(적의 방어력 + 800 + 8×캐릭터 레벨))
	float DefenceEffect = 1.0f - (TargetDefence / (TargetDefence + 800.0f));
	// 캐릭터 공격력, 다양한 공격력 증가 요소, 크리티컬 수치는 적용된 상태로 값이 들어와야 함
	const float FinalDamage = AppliedSourceDamage * DefenceEffect;
	// Debug::Print(TEXT("FinalDamage"), FinalDamage);


	// 출력 : 여러 Attribute 중 필요한 값들을 변경
	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetWWAttributeSetCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
	if (SourceStaggerDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetEliteAttributeSetCapture().StaggerDamageTakenProperty,
				EGameplayModOp::Override,
				SourceStaggerDamage
			)
		);
	}
	if (SourceParryDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetEliteAttributeSetCapture().ParryDamageTakenProperty,
				EGameplayModOp::Override,
				SourceParryDamage
			)
		);
	}
}
