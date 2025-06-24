// Fill out your copyright notice in the Description page of Project Settings.

#include "WWCopy/Public/Controllers/WWPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Characters/Player/PlayerCharacter.h"
#include "InputActionValue.h"
#include "WWGameplayTags.h"
#include "Components/WWEnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"

void AWWPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// check Input Config Data Asset
	if (!InputConfigDataAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Input Config Data Asset is null"), *GetNameSafe(this));
		return;
	}

	// Check Enhanced Input Subsystem and add mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Enhanced Input Subsystem is null"), *GetNameSafe(this));	
	}

	// Bind Input Action
	UWWEnhancedInputComponent* WWInputComponent = CastChecked<UWWEnhancedInputComponent>(InputComponent);
	WWInputComponent->BindNativeInputAction(InputConfigDataAsset, WWGameplayTags::InputTag_Move, ETriggerEvent::Triggered,
		this, &AWWPlayerController::Input_Move);
	WWInputComponent->BindNativeInputAction(InputConfigDataAsset, WWGameplayTags::InputTag_Look, ETriggerEvent::Triggered,
		this, &AWWPlayerController::Input_Look);
	WWInputComponent->BindAbilityInputAction(InputConfigDataAsset, this,
		&AWWPlayerController::Input_AbilityInputPressed, &AWWPlayerController::Input_AbilityInputReleased);
	
	
}

void AWWPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	if (!PossessedPlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Possessed Player Character is null"), *GetNameSafe(this));
		return;
	}
	PossessedPlayerCharacter->Move(InputActionValue);
}

void AWWPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	if (!PossessedPlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Possessed Player Character is null"), *GetNameSafe(this));
		return;
	}
	PossessedPlayerCharacter->Look(InputActionValue);
}

void AWWPlayerController::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	if (!PossessedPlayerCharacter)
	{
		return;
	}
	PossessedPlayerCharacter->AbilityInputPressed(InputTag);
}

void AWWPlayerController::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	if (!PossessedPlayerCharacter)
	{
		return;
	}
	PossessedPlayerCharacter->AbilityInputReleased(InputTag);
}

void AWWPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedPlayerCharacter = Cast<APlayerCharacter>(InPawn);
	checkf(PossessedPlayerCharacter, TEXT("%s: Player Character is null"), *GetNameSafe(this));
}
