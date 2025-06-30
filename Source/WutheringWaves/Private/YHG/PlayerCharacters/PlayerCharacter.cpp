// Fill out your copyright notice in the Description page of Project Settings.

#include "WutheringWaves/Public/YHG/PlayerCharacters/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//스프링암 초기세팅
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	//카메라 초기세팅
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//케릭터움직임 초기세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;

	//메시 -90도 돌려놓아 정면으로 조정
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}
