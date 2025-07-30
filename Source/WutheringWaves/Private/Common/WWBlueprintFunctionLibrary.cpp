// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/WWBlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Common/Interfaces/PawnCombatInterface.h"

UWWAbilitySystemComponent* UWWBlueprintFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);

	return CastChecked<UWWAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}


void UWWBlueprintFunctionLibrary::AddTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UWWAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);

	//어빌리티시스템에 등록된 태그를 체크하여 매칭이 되지 않으면 어빌리티 시스템에 추가 
	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->AddLooseGameplayTag(Tag);
	}
}

void UWWBlueprintFunctionLibrary::RemoveTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UWWAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);

	//어빌리티시스템에 등록이 되어있으면 태그를 체크하여 어빌리티 시스템에서 제외 
	if (ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->RemoveLooseGameplayTag(Tag);
	}
}

bool UWWBlueprintFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	UWWAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	return ASC->HasMatchingGameplayTag(Tag);
}

FActiveGameplayEffectHandle UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (ASC)
	{
		if (InGameplayEffectSpecHandle.IsValid())
		{
			return ASC->ApplyGameplayEffectSpecToTarget(*InGameplayEffectSpecHandle.Data, ASC);
		}
		else
		{
			//Debug::Print(TEXT("ApplyGameplayEffectSpecHandleToTarget : InGameplayEffectSpecHandle is Invalid"));
			return FActiveGameplayEffectHandle();
		}
	}
	return FActiveGameplayEffectHandle();
}

void UWWBlueprintFunctionLibrary::BP_HasTag(AActor* Actor, FGameplayTag Tag, EWWConfirmType& OutType)
{
	OutType = NativeActorHasTag(Actor, Tag) ? EWWConfirmType::Yes : EWWConfirmType::No;
}

UPawnCombatComponent* UWWBlueprintFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* Actor)
{
	check(Actor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(Actor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UWWBlueprintFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* Actor,
	EWWValidType& OutValid)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(Actor);
	OutValid = CombatComponent ? EWWValidType::Valid : EWWValidType::InValid;

	return CombatComponent;
}

bool UWWBlueprintFunctionLibrary::IsTargetPawnHostile(APawn* OwningPawn, APawn* TagetPawn)
{
	check(OwningPawn && TagetPawn);

	IGenericTeamAgentInterface* OwningTeamAgent = Cast<IGenericTeamAgentInterface>(OwningPawn->GetController());
	IGenericTeamAgentInterface* TagetTeamAgent = Cast<IGenericTeamAgentInterface>(TagetPawn->GetController());

	if (OwningTeamAgent && TagetTeamAgent)
	{
		return OwningTeamAgent->GetGenericTeamId() != TagetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UWWBlueprintFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& ScFloat, float Level)
{
	return ScFloat.GetValueAtLevel(Level);
}

bool UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor,
                                                                             const FGameplayEffectSpecHandle&
                                                                             SpecHandle)
{
	UWWAbilitySystemComponent* SourceASC = NativeGetAbilitySystemComponentFromActor(Instigator);
	UWWAbilitySystemComponent* TargetASC = NativeGetAbilitySystemComponentFromActor(TargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(
		*SpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UWWBlueprintFunctionLibrary::SeamlessTravel(UObject* WorldContextObject, const FString& MapReferencePath)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FString FullMapURL = FString::Printf(TEXT("%s?listen"), *MapReferencePath);
		World->ServerTravel(FullMapURL);
	}
}


/*
bool UWWBlueprintFunctionLibrary::IsValidBlock(AActor* Attacker, AActor* Defender)
{
	check(Attacker && Defender);

	// [-1,1] 마주볼수록 -1에 근접
	const float DotResult = FVector::DotProduct(Attacker->GetActorForwardVector(), Defender->GetActorForwardVector());

	const FString DebugString = FString::Printf(TEXT("DotResult : %f %s"), DotResult,DotResult < 0.1f ? TEXT("Valid Block") : TEXT("Invalid Block"));

	Debug::Print(DebugString,DotResult < 0.1f ? FColor::Green : FColor::Red);

	return DotResult < 0.1f;
}
*/
/*
FGameplayTag UWWBlueprintFunctionLibrary::ComputeHitReactDirectionTag(AActor* Attacker, AActor* HitActor,
	float& OutAngleDiff)
{
	check(Attacker && HitActor);

	const FVector HitForward = HitActor->GetActorForwardVector();
	const FVector HitToAttackerNormalized = (Attacker->GetActorLocation() - HitActor->GetActorLocation()).
		GetSafeNormal();

	// Dot Product : 각도 추출
	const float DotResult = FVector::DotProduct(HitForward, HitToAttackerNormalized);
	OutAngleDiff = UKismetMathLibrary::DegAcos(DotResult);

	// Cross Product : 좌/우 판별
	const FVector CrossResult = FVector::CrossProduct(HitForward, HitToAttackerNormalized);
	if (CrossResult.Z < 0.f)
	{
		OutAngleDiff *= -1.f;
	}

	if (OutAngleDiff >= -45.f && OutAngleDiff <= 45.f)
	{
		return BaseGamePlayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference > 45.f && OutAngleDiff < 135.f)
	{
		return BaseGamePlayTags::Shared_Status_HitReact_Right;
	}
	else if (OutAngleDifference > -135.f && OutAngleDiff < -45.f)
	{
		return BaseGamePlayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference >= 135.f || OutAngleDiff <= -135.f)
	{
		return BaseGamePlayTags::Shared_Status_HitReact_Back;
	}
	return BaseGamePlayTags::Shared_Status_HitReact_Front;
}

*/
