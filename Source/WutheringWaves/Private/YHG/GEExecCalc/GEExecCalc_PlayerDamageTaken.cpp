// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/GEExecCalc/GEExecCalc_PlayerDamageTaken.h"

#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAttributeSet.h"

struct FDamageCapture
{
	//BaseAttributeSet에 변수를 캡처
	DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyAttack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyDefense)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FDamageCapture()
	{
		//Source GE - 생성주체, Target GE - 적용대상
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyAttack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyDefense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, DamageTaken, Target, false);
	}
};


static const FDamageCapture& GetDamageCapture()
{
	static FDamageCapture DamageCapture;
	return DamageCapture;
}


UGEExecCalc_PlayerDamageTaken::UGEExecCalc_PlayerDamageTaken()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().ApplyAttackDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().ApplyDefenseDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
}

void UGEExecCalc_PlayerDamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	//주입한 스팩 얻어오기
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().ApplyAttackDef, EvaluateParameters, SourceAttack);
	
	float BaseDamage = 0.f;
	int32 CachedComboCount_Light = 0;
	
	//EffectSpec에서 BaseDamage와 콤보카운트_라이트, 콤보카운트_해비를 추출하여 변수에 적용
	for (const TPair<FGameplayTag, float>& TagMagnitude  : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			CachedComboCount_Light = TagMagnitude.Value;
			//Debug::Print(TEXT("CachedComboCount_Light"), CachedComboCount_Light);
		}
	}

	float TargetDefence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().ApplyDefenseDef, EvaluateParameters, TargetDefence);
	
	if (CachedComboCount_Light != 0)
	{
		//여기 계산식
		const float LightDamageIncrePercent = (CachedComboCount_Light -1) * 0.05f + 1.0f;
		BaseDamage *= LightDamageIncrePercent;
	}

	const float FinalDamage = BaseDamage * SourceAttack / TargetDefence;
	
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