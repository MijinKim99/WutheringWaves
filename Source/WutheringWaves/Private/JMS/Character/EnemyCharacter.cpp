// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Character/EnemyCharacter.h"

#include "MotionWarpingComponent.h"
#include "Common/WWDebugHelper.h"
#include "Common/DataAssets/DataAsset_Startup.h"
#include "Components/BoxComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/Component/EnemyCombatComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionBox"));
	AttackCollisionBox->SetupAttachment(GetMesh());
	AttackCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

UPawnCombatComponent* AEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AEnemyCharacter::GetPawnUIComponent() const
{
	return Super::GetPawnUIComponent();
}

UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() const
{
	return Super::GetEnemyUIComponent();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::SetAttackTransformFromMotionWarpingTarget(FName WarpTargetName)
{
	const FMotionWarpingTarget* Target = MotionWarpingComponent->FindWarpTarget(WarpTargetName);
	if (Target)
	{
		EnemyCombatComponent->SetAttackTransform(FTransform(FRotator(0.f, GetActorRotation().Yaw, 0.f),
		                                                    Target->GetLocation(),
		                                                    FVector(1.f, 1.f, 1.f)));
	}
	else
	{
		EnemyCombatComponent->SetAttackTransform(GetActorTransform());
	}
}

void AEnemyCharacter::InitEnemyStartUpData()
{
	if (StartupData.IsNull())
	{
		return;
	}

	//Startup data를 비동기 로딩으로 불러온다.
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_Startup* LoadedData = StartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(WWAbilitySystemComponent);
					Debug::Print(TEXT("Enemy Async StartupData Loaded"), FColor::Green);
				}
			}
		)
	);
}
