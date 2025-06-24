// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWCopy/Public/Characters/WWCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPawnUIComponent;
class UPlayerUIComponent;
struct FGameplayTag;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class WWCOPY_API APlayerCharacter : public AWWCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	
#pragma region Input
public:
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);

	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
#pragma endregion

public:
	// IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;
	// End of IPawnUIInterface

#pragma region Component

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	UPlayerUIComponent* PlayerUIComponent;
#pragma endregion
};
