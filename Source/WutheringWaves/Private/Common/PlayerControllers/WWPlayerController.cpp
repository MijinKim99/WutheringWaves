// Fill out your copyright notice in the Description page of Project Settings.


#include "WutheringWaves/Public/Common/PlayerControllers/WWPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "Common/Components/WWHUDSharedUIComponent.h"
#include "Common/PlayerStates/WWPlayerState.h"
#include "YHG/Components/Input/WWEnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

AWWPlayerController::AWWPlayerController()
{
	IsInputMove = FVector2D(0.0f, 0.0f);
	bIsInputDash = false;
	bIsInputJump = false;
	bIsInputLightAttack = false;
	
	HeroTeamID = FGenericTeamId(0);

	HUDSharedUIComponent = CreateDefaultSubobject<UWWHUDSharedUIComponent>(TEXT("HUDSharedUIComponent"));
}

FGenericTeamId AWWPlayerController::GetGenericTeamId() const
{
	return HeroTeamID;
}

APlayerCharacter* AWWPlayerController::GetControlledPlayerCharacter() const
{
	return ControlledPlayerCharacter;
}

void AWWPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ControlledPlayerCharacter = Cast<APlayerCharacter>(InPawn);
	// OnPossessDelegate.Broadcast(InPawn);
}

void AWWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!DataAsset_InputConfig)
	{
		//Debug::Print(TEXT("WWPlayerController : Can't find DataAsset_InputConfig"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());

	if (!Subsystem)
	{
		//Debug::Print(TEXT("WWPlayerController : Can't find Subsystem"));
		return;
	}

	Subsystem->AddMappingContext(DataAsset_InputConfig->DefaultMappingContext, 0);

	UWWEnhancedInputComponent* WWEnhancedInputComponent = Cast<UWWEnhancedInputComponent>(InputComponent);
	if (!WWEnhancedInputComponent)
	{
		//Debug::Print(TEXT("WWPlayerController : Cast Failed WWEnhancedInputComponent"));
		return;
	}

	WWEnhancedInputComponent->BindNativeInputAction(
		DataAsset_InputConfig,
		WWGameplayTags::InputTag_Move,
		ETriggerEvent::Triggered,
		this,
		&AWWPlayerController::Input_Move);

	WWEnhancedInputComponent->BindNativeInputAction(
		DataAsset_InputConfig,
		WWGameplayTags::InputTag_Look,
		ETriggerEvent::Triggered,
		this,
		&AWWPlayerController::Input_Look);

	WWEnhancedInputComponent->BindAbilityInputAction(
		DataAsset_InputConfig,
		this,
		&AWWPlayerController::Input_AbilityInputPressed,
		&AWWPlayerController::Input_AbilityInputReleased);
}

void AWWPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
}

void AWWPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddPitchInput(LookAxisVector.Y);
	}
}

void AWWPlayerController::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	UWWAbilitySystemComponent* WWAbilitySystemComponent = Cast<UWWAbilitySystemComponent>(GetPlayerState<AWWPlayerState>()->GetAbilitySystemComponent());
	if (!WWAbilitySystemComponent)
	{
		//Debug::Print(TEXT("WWPlayerController : Failed Cast WWAbilitySystemComponent"));
		return;
	}
	
	WWAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void AWWPlayerController::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	UWWAbilitySystemComponent* WWAbilitySystemComponent = Cast<UWWAbilitySystemComponent>(GetPlayerState<AWWPlayerState>()->GetAbilitySystemComponent());
	if (!WWAbilitySystemComponent)
	{
		//Debug::Print(TEXT("WWPlayerController : Failed Cast WWAbilitySystemComponent"));
		return;
	}
	
	WWAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}

UWWHUDSharedUIComponent* AWWPlayerController::GetHUDSharedUIComponent() const
{
	return HUDSharedUIComponent;
}
