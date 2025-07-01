#pragma once
#include "GameplayTagContainer.h"
#include "YHGStructType.generated.h"

class UWWGameplayAbility;
class UInputAction;

USTRUCT(BlueprintType)
struct FWWInputActionConfig
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};


USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories="InputTag"))
	FGameplayTag InputTag;

	//부여가능한 능력
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWWGameplayAbility> AbilityToGrant;
};

class YHGStructType
{
public:
	
};
