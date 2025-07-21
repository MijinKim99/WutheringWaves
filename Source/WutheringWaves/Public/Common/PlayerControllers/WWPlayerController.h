// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"

class AWWPlayerState;
class APlayerCharacter;
struct FGameplayTag;
struct FInputActionValue;
class UInputConfig;

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AWWPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AWWPlayerController();
	virtual FGenericTeamId GetGenericTeamId() const override;

	APlayerCharacter* GetControlledPlayerCharacter() const;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputConfig* DataAsset_InputConfig;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* ControlledPlayerCharacter;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "NativeInputControl")
	FVector2D IsInputMove;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityInputControl")
	bool bIsInputDash;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityInputControl")
	bool bIsInputJump;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityInputControl")
	bool bIsInputLightAttack;

private:
	FGenericTeamId HeroTeamID;
};
