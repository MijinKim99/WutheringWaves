// Fill out your copyright notice in the Description page of Project Settings.


#include "WWCopy/Public/Characters/Player/PlayerCharacter.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/WWAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/UI/PlayerUIComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	//스프링암 초기세팅
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.f, 55.0f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	//카메라 초기세팅
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//캐릭터 움직임 초기세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.5f, 500.0f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	//매시 초기위치 세팅
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, - 100.0f), FRotator(0.f, -90.0f, 0.0f));

	// UIComponent
	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));
}

void APlayerCharacter::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::AbilityInputPressed(FGameplayTag InputTag)
{
	WWAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void APlayerCharacter::AbilityInputReleased(FGameplayTag InputTag)
{
	WWAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}

UPawnUIComponent* APlayerCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* APlayerCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}
