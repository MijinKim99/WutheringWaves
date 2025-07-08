// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/Components/WWCharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "EngineStats.h"
#include "Engine/NetConnection.h"
#include "GameFramework/WorldSettings.h"
#include "UObject/Package.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

FVector UWWCharacterMovementComponent::ConstrainAnimRootMotionVelocity(const FVector& RootMotionVelocity,
	const FVector& CurrentVelocity) const
{
	return RootMotionVelocity;
}