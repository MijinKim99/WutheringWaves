// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AbilitySystem/GEExecCalc/GEExecClac_EnemyDamageTaken.h"

#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAttributeSet.h"

struct FDamageCapture
{
	//BaseAttributeSet에 변수를 캡처
	DECLARE_ATTRIBUTE_CAPTUREDEF(BasicAttack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BasicDefense)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FDamageCapture()
	{
		//Source GE - 생성주체, Target GE - 적용대상
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, BasicAttack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, BasicDefense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, DamageTaken, Target, false);
	}
};
static const FDamageCapture& GetDamageCapture()
{
	static FDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecClac_EnemyDamageTaken::UGEExecClac_EnemyDamageTaken()
{
	//RelevantAttributesToCapture 주입
	RelevantAttributesToCapture.Add(GetDamageCapture().BasicAttackDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().BasicDefenseDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
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

	float SourceAttack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().BasicAttackDef, EvaluateParameters, SourceAttack);
	Debug::Print(TEXT("SourceAttack"), SourceAttack);
	
	float PhysicalDamage = 0.f;
	
	//EffectSpec에서 BaseDamage를 추출하여 변수에 적용
	for (const TPair<FGameplayTag, float>& TagMagnitude  : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Physical))
		{
			PhysicalDamage = TagMagnitude.Value;
			Debug::Print(TEXT("PhysicalDamage"), PhysicalDamage);
		}
	}

	float TargetDefence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().BasicDefenseDef, EvaluateParameters, TargetDefence);
	Debug::Print(TEXT("TargetDefence"), TargetDefence);

	

	const float FinalDamage = PhysicalDamage * SourceAttack / TargetDefence;
	Debug::Print(TEXT("FinalDamage"), FinalDamage);
	
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
