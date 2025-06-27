// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "WWCharacter.generated.h"

class UWWAbilitySystemComponent;
class UWWAttributeSet;
class USkeletalMeshComponent;

UCLASS()
class WWCOPY_API AWWCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnUIInterface
{
	GENERATED_BODY()

#pragma region AbilitySystem
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UWWAbilitySystemComponent* WWAbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UWWAttributeSet* WWAttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion 
	
public:
	// Sets default values for this character's properties
	AWWCharacter();

	// IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	// End of IPawnUIInterface

protected:
	virtual void BeginPlay() override;

};
