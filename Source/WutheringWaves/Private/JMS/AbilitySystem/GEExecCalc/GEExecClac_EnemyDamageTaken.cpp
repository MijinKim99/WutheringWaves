// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AbilitySystem/GEExecCalc/GEExecClac_EnemyDamageTaken.h"

#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAttributeSet.h"
#include "JMS/AbilitySystem/AttributeSet/EnemyAttributeSet.h"

struct FDamageCapture
{
	//BaseAttributeSet에 변수를 캡처
	//DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyAttack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyDefense)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	
	

	FDamageCapture()
	{
		//Source GE - 생성주체, Target GE - 적용대상
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyAttack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyDefense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, DamageTaken, Target, false);
		
	}
};
static const FDamageCapture& GetDamageCapture()
{
	static FDamageCapture DamageCapture;
	return DamageCapture;
}

struct FResistanceCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(WindResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DarkResistance)
	FResistanceCapture()
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

static const FResistanceCapture& GetResistanceCapture()
{
	static FResistanceCapture ResistanceCapture;
	return ResistanceCapture;
}

UGEExecClac_EnemyDamageTaken::UGEExecClac_EnemyDamageTaken()
{
	//RelevantAttributesToCapture 주입
	//RelevantAttributesToCapture.Add(GetDamageCapture().ApplyAttackDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().ApplyDefenseDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
	RelevantAttributesToCapture.Add(GetResistanceCapture().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(GetResistanceCapture().IceResistanceDef);
	RelevantAttributesToCapture.Add(GetResistanceCapture().FireResistanceDef);
	RelevantAttributesToCapture.Add(GetResistanceCapture().LightningResistanceDef);
	RelevantAttributesToCapture.Add(GetResistanceCapture().WindResistanceDef);
	RelevantAttributesToCapture.Add(GetResistanceCapture().LightResistanceDef);
	RelevantAttributesToCapture.Add(GetResistanceCapture().DarkResistanceDef);
}

void UGEExecClac_EnemyDamageTaken::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	//주입한 스팩 얻어오기
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	// Source 속성 대미지
	// float SourceAttack = 0.f;
	// ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().ApplyAttackDef, EvaluateParameters, SourceAttack);
	// Debug::Print(TEXT("SourceAttack"), SourceAttack);


	
	// Targe 속성 저항
	float TargetPhysicalResistance = 0.f;
	float TargetIceResistance = 0.f;
	float TargetFireResistance = 0.f;
	float TargetLightningResistance = 0.f;
	float TargetWindResistance = 0.f;
	float TargetLightResistance = 0.f;
	float TargetDarkResistance = 0.f;

	// 속성 저항 불러오기
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetResistanceCapture().PhysicalResistanceDef, EvaluateParameters, TargetPhysicalResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetResistanceCapture().IceResistanceDef, EvaluateParameters, TargetIceResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetResistanceCapture().FireResistanceDef, EvaluateParameters, TargetFireResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetResistanceCapture().LightningResistanceDef, EvaluateParameters, TargetLightningResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetResistanceCapture().WindResistanceDef, EvaluateParameters, TargetWindResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetResistanceCapture().LightResistanceDef, EvaluateParameters, TargetLightResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetResistanceCapture().DarkResistanceDef, EvaluateParameters, TargetDarkResistance);
	
	// EffectSpec에서 ApplyDamage를 추출하여 변수에 적용
	// 저항력에 대한 대미지 계산 : 대미지 * (1-저항)
	float SourcePhysicalDamage = 0.f;
	float SourceIceDamage = 0.f;
	float SourceFireDamage = 0.f;
	float SourceLightningDamage = 0.f;
	float SourceWindDamage = 0.f;
	float SourceLightDamage = 0.f;
	float SourceDarkDamage = 0.f;
	for (const TPair<FGameplayTag, float>& TagMagnitude  : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Physical))
		{
			SourcePhysicalDamage = TagMagnitude.Value;
			SourcePhysicalDamage *= (1.f - TargetPhysicalResistance);
			Debug::Print(TEXT("PhysicalDamage"), SourcePhysicalDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Ice))
		{
			SourceIceDamage = TagMagnitude.Value;
			SourceIceDamage *= (1.f - TargetIceResistance);
			Debug::Print(TEXT("IceDamage"), SourceIceDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Fire))
		{
			SourceFireDamage = TagMagnitude.Value;
			SourceFireDamage *= (1.f - TargetFireResistance);
			Debug::Print(TEXT("FireDamage"), SourceFireDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Lightning))
		{
			SourceLightningDamage = TagMagnitude.Value;
			SourceLightningDamage *= (1.f - TargetLightningResistance);
			Debug::Print(TEXT("LightningDamage"), SourceLightningDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Wind))
		{
			SourceWindDamage = TagMagnitude.Value;
			SourceWindDamage *= (1.f - TargetWindResistance);
			Debug::Print(TEXT("WindDamage"), SourceWindDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Light))
		{
			SourceLightDamage = TagMagnitude.Value;
			SourceLightDamage *= (1.f - TargetLightResistance);
			Debug::Print(TEXT("LightDamage"), SourceLightDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Dark))
		{
			SourceDarkDamage = TagMagnitude.Value;
			SourceDarkDamage *= (1.f - TargetDarkResistance);
			Debug::Print(TEXT("DarkDamage"), SourceDarkDamage);
		}
	}
	float TargetDefence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().ApplyDefenseDef, EvaluateParameters, TargetDefence);
	Debug::Print(TEXT("TargetDefence"), TargetDefence);

	// 현재는 한번에 하나의 대미지만 들어옴
	float AppliedSourceDamage = SourcePhysicalDamage + SourceIceDamage + SourceFireDamage + SourceLightningDamage + SourceWindDamage + SourceLightDamage + SourceDarkDamage;
	// 방어력에 의한 영향 : 1 - (적의 방어력/(적의 방어력 + 800 + 8×캐릭터 레벨))
	float DefenceEffect = 1.0f-(TargetDefence/(TargetDefence + 800.0f));
	// 캐릭터 공격력, 다양한 공격력 증가 요소, 크리티컬 수치는 적용된 상태로 값이 들어와야 함
	const float FinalDamage = AppliedSourceDamage * DefenceEffect;
	Debug::Print(TEXT("FinalDamage"), FinalDamage);


	// 현재는 주어진 대미지 수치만 DamageTaken 어트리뷰트에 Override
	// 어떤 속성의 대미지가 들어왔는지 표시하려면 아래 코드를 참고해서 추가 구현 필요
	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
			GetDamageCapture().DamageTakenProperty,
						EGameplayModOp::Override,
						FinalDamage
			)
		);
	}
}
