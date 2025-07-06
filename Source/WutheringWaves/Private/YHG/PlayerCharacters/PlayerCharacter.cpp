// Fill out your copyright notice in the Description page of Project Settings.

#include "WutheringWaves/Public/YHG/PlayerCharacters/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Common/DataAssets/DataAsset_Startup.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "YHG/Components/Combat/PlayerCombatComponent.h"

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

	//CombatComponent 세팅
	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));

	//케릭터움직임 초기세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	GetCharacterMovement()->JumpZVelocity = 840.0f;
	GetCharacterMovement()->GravityScale = 2.0f;

	//메시 -90도 돌려놓아 정면으로 조정
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	AttackMode = false;
	
	LightAttackComboCount = 1;
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	}
	else
	{
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	}

	//상태 정의 코드
	bIsGrounded = GetCharacterMovement()->IsMovingOnGround();
	bIsFalling = GetCharacterMovement()->IsFalling() && (GetCharacterMovement()->Velocity.Z < 0);
	//아무런 움직임이 없고, 지상일 때
	bIsIdle = GetCharacterMovement()->Velocity.IsZero() && bIsGrounded;

	//카메라 기준 오른쪽으로 움직이는지, 왼쪽으로 움직이는지
	FVector VelocityDirection = GetCharacterMovement()->Velocity.GetSafeNormal();
	bIsLeftMoving = UKismetMathLibrary::Cross_VectorVector(VelocityDirection, FollowCamera->GetForwardVector()).Z > 0;
	bIsRightMoving = UKismetMathLibrary::Cross_VectorVector(VelocityDirection, FollowCamera->GetForwardVector()).Z < 0;

	if ((bIsLeftMoving && bIsRightMoving) || (!bIsLeftMoving && !bIsRightMoving))
	{
		if (FMath::RandBool())
		{
			bIsLeftMoving = true;
			bIsRightMoving = false;
		}
		else
		{
			bIsLeftMoving = false;
			bIsRightMoving = true;
		}
	}
	
	//지상 움직임
	bIsRun = GetCharacterMovement()->GetCurrentAcceleration().SizeSquared2D() > 0.f && bIsGrounded;
	
	bIsLeftJumping = bIsLeftMoving && ((GetCharacterMovement()->Velocity.Z) > (GetCharacterMovement()->JumpZVelocity / 2));
	bIsRightJumping = bIsRightMoving && ((GetCharacterMovement()->Velocity.Z) > (GetCharacterMovement()->JumpZVelocity / 2));
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!StartupData.IsNull())
	{
		if (UDataAsset_Startup* LoadedData = StartupData.LoadSynchronous())
		{
			//Startup데이터가 Null이 아닌경우 StartupData는 동기화로드를 거쳐서 최종적으로 게임어빌리티시스템이 발동된다. 
			LoadedData->GiveToAbilitySystemComponent(WWAbilitySystemComponent);
		}
	}
}

bool APlayerCharacter::GetIsGrounded() const
{
	return bIsGrounded;
}

bool APlayerCharacter::GetIsFalling() const
{
	return bIsFalling;
}


bool APlayerCharacter::GetIsIdle() const
{
	return bIsIdle;
}

bool APlayerCharacter::GetIsRightMoving() const
{
	return bIsRightMoving;
}

bool APlayerCharacter::GetIsLeftMoving() const
{
	return bIsLeftMoving;
}

bool APlayerCharacter::GetIsRun() const
{
	return bIsRun;
}

bool APlayerCharacter::GetIsLeftJumping() const
{
	return bIsLeftJumping;
}

bool APlayerCharacter::GetIsRightJumping() const
{
	return bIsRightJumping;
}
