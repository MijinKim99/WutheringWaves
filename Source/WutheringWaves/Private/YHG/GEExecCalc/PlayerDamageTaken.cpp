// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/GEExecCalc/PlayerDamageTaken.h"

#include "JMS/AbilitySystem/GEExecCalc/GEExecClac_EnemyDamageTaken.h"

#include "Common/WWDebugHelper.h"	
#include "Common/WWGameplayTags.h"
#include "YHG/AbilitySystem/PlayerCharacterAttributeSet.h"

struct FEnemyDamageCapture
{
	//BaseAttributeSet에 변수를 캡처
	//DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyAttack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ApplyDefense)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	
	FEnemyDamageCapture()
	{
		//Source GE - 생성주체, Target GE - 적용대상
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UWWAttributeSet, ApplyAttack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerCharacterAttributeSet, ApplyDefense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerCharacterAttributeSet, DamageTaken, Target, false);
		
	}
};
static const FEnemyDamageCapture& GetEnemyDamageCapture()
{
	static FEnemyDamageCapture EnemyDamageCapture;
	return EnemyDamageCapture;
}

UPlayerDamageTaken::UPlayerDamageTaken()
{
	//RelevantAttributesToCapture 주입
	//RelevantAttributesToCapture.Add(GetDamageCapture().ApplyAttackDef);
	RelevantAttributesToCapture.Add(GetEnemyDamageCapture().ApplyDefenseDef);
	RelevantAttributesToCapture.Add(GetEnemyDamageCapture().DamageTakenDef);
}

void UPlayerDamageTaken::Execute_Implementation(
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
	
	// EffectSpec에서 ApplyDamage를 추출하여 변수에 적용
	float SourcePhysicalDamage = 0.f;
	for (const TPair<FGameplayTag, float>& TagMagnitude  : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WWGameplayTags::Shared_SetByCaller_Damage_Physical))
		{
			SourcePhysicalDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("PhysicalDamage"), SourcePhysicalDamage);
		}
	}
	float TargetDefense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEnemyDamageCapture().ApplyDefenseDef, EvaluateParameters, TargetDefense);
	//Debug::Print(TEXT("TargetDefense"), TargetDefense);

	// 현재는 한번에 하나의 대미지만 들어옴
	float AppliedSourceDamage = SourcePhysicalDamage;
	// 방어력에 의한 영향 : 1 - (적의 방어력/(적의 방어력 + 800 + 8×캐릭터 레벨))
	float DefenseEffect = 1.0f-(TargetDefense/(TargetDefense + 800.0f));
	// 캐릭터 공격력, 다양한 공격력 증가 요소, 크리티컬 수치는 적용된 상태로 값이 들어와야 함
	const float FinalDamage = AppliedSourceDamage * DefenseEffect;
	//Debug::Print(TEXT("FinalDamage"), FinalDamage);


	// 현재는 주어진 대미지 수치만 DamageTaken 어트리뷰트에 Override
	// 어떤 속성의 대미지가 들어왔는지 표시하려면 아래 코드를 참고해서 추가 구현 필요
	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
			GetEnemyDamageCapture().DamageTakenProperty,
						EGameplayModOp::Override,
						FinalDamage
			)
		);
	}
}
