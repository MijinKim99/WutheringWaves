// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Character/EnemyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "MotionWarpingComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAttributeSet.h"
#include "Common/Components/WWHUDSharedUIComponent.h"
#include "Common/DataAssets/DataAsset_Startup.h"
#include "Common/Widget/WWUserWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/AbilitySystem/AttributeSet/EnemyAttributeSet.h"
#include "JMS/Component/EnemyCombatComponent.h"
#include "KMJ/UIComponents/EnemyUIComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>("EnemyAttributeSet");
	WWAttributeSet = CreateDefaultSubobject<UWWAttributeSet>("WWAttributeSet");
	WWAbilitySystemComponent = CreateDefaultSubobject<UWWAbilitySystemComponent>(TEXT("WWAbilitySystemComponent"));
	WWHUDSharedUIComponent = CreateDefaultSubobject<UWWHUDSharedUIComponent>(TEXT("WWHUDSharedUIComponent"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());

	EnemyName = FText::FromName(FName(TEXT("적 이름을 입력하세요")));
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (WWAbilitySystemComponent)
	{
		WWAbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitEnemyStartUpData();
	}
	else
	{
		//Debug::Print(FString::Printf(TEXT("%s : WWAbilitySystemComponent is Null"), *GetNameSafe(this)), FColor::Red);
	}
}

UPawnCombatComponent* AEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

FText AEnemyCharacter::GetEnemyName() const
{
	return EnemyName;
}

void AEnemyCharacter::HideWidgetComponent()
{
	if (WidgetComponent)
	{
		WidgetComponent->SetHiddenInGame(true);
	}
}

UPawnUIComponent* AEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const
{
	return WWAbilitySystemComponent;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UWWUserWidget* HealthWidget = Cast<UWWUserWidget>(WidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreateWidget(this);
	}
}

UWWHUDSharedUIComponent* AEnemyCharacter::GetHUDSharedUIComponent() const
{
	return WWHUDSharedUIComponent;
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
					//Debug::Print(TEXT("Enemy Async StartupData Loaded"), FColor::Green);
					OnInitialized.Broadcast();
				}
			}
		)
	);
}

void AEnemyCharacter::CancelEnemyActiveAbilities(UAbilitySystemComponent* ASC, FGameplayTag CancelTag)
{
	if (!ASC || !CancelTag.IsValid())
	{
		//Debug::Print(TEXT("EnemyCharacter : CancelEnemyActiveAbilities, Can't find ASC or CancelTag"));
		return;
	}

	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (!Spec.IsActive())
			continue;

		const UGameplayAbility* AbilityCDO = Spec.Ability;
		if (!AbilityCDO)
			continue;

		// 어빌리티에 태그가 포함되어 있으면
		if (AbilityCDO->AbilityTags.HasTagExact(CancelTag))
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}

void AEnemyCharacter::CancelEnemyAllActiveAbilities(UAbilitySystemComponent* ASC)
{
	if (!ASC)
	{
		//Debug::Print(TEXT("EnemyCharacter : CancelEnemyAllActiveAbilities, Can't find ASC"));
		return;
	}

	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (Spec.IsActive())
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}
