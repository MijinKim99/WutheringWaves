// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"

struct FInputActionValue;
class UDataAsset_InputConfig;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AWWPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* DataAsset_InputConfig;
	
	virtual void SetupInputComponent() override;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
};
