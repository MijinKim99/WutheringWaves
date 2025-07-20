// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Character/EliteEnemyCharacter.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWGameplayTags.h"
#include "JMS/AbilitySystem/AttributeSet/EliteAttributeSet.h"
#include "JMS/Character/LordEnemyCharacter.h"

AEliteEnemyCharacter::AEliteEnemyCharacter()
{
	EliteAttributeSet = CreateDefaultSubobject<UEliteAttributeSet>(TEXT("EliteAttributeSet"));
}
void AEliteEnemyCharacter::StartParryEvent()
{
	GetWorld()->GetTimerManager().SetTimer(EnableParryTimerHandle, this, &ALordEnemyCharacter::EnableParry,
										   ParryGuideDuration, false);
	GetWorld()->GetTimerManager().SetTimer(UpdateGuideDurationTimerHandle, this,
										   &ALordEnemyCharacter::UpdateGuideDuration, UpdateInterval, true);
	ParryGuideDurationCounter = 0.f;
	ParryEnableDurationCounter = 0.f;
	Debug::Print(TEXT("Parry Event Started : ALordEnemyCharacter::StartParryEvent()"), FColor::Red);
}

void AEliteEnemyCharacter::EnableParry()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	UWWBlueprintFunctionLibrary::AddTagToActor(this,WWGameplayTags::Enemy_Status_ParryEnabled);
	GetWorld()->GetTimerManager().SetTimer(DisableParryTimerHandle, this, &ALordEnemyCharacter::DisableParry,
										   ParryEnableDuration, false);
	GetWorld()->GetTimerManager().SetTimer(UpdateEnableDurationTimerHandle, this,
										   &ALordEnemyCharacter::UpdateEnableDuration, UpdateInterval, true);
	Debug::Print(TEXT("Parry Enabled : ALordEnemyCharacter::EnableParry()"), FColor::Red);
}

void AEliteEnemyCharacter::DisableParry()
{
	UWWBlueprintFunctionLibrary::RemoveTagFromActor(this, WWGameplayTags::Enemy_Status_ParryEnabled);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Debug::Print(TEXT("Parry Disabled : ALordEnemyCharacter::DisableParry()"), FColor::Red);
}

void AEliteEnemyCharacter::UpdateGuideDuration()
{
	ParryGuideDurationCounter += UpdateInterval;
	Debug::Print(FString::Printf(TEXT("Parry Guide Duration : %f"), ParryGuideDurationCounter), FColor::Red, 10);
}

void AEliteEnemyCharacter::UpdateEnableDuration()
{
	ParryEnableDurationCounter += UpdateInterval;
	Debug::Print(FString::Printf(TEXT("Parry Enable Duration : %f"), ParryEnableDurationCounter), FColor::Red, 10);
}
