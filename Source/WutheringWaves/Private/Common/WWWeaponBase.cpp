// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/WWWeaponBase.h"

#include "Components/BoxComponent.h"

// Sets default values
AWWWeaponBase::AWWWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
    
	WeaponCollsionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollsionBox->SetupAttachment(RootComponent);
	WeaponCollsionBox->SetBoxExtent(FVector(20.0f));
	WeaponCollsionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWWWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GetInstigator 이벤트를 발생시킨 포인터 누가 데미지를 입혔는가 T클래스 반환(주체대상)
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to Assign an instigator as the owning pawn of the weapon: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		//피아식별을 하여 타겟이 아군이 아닐경우 전달
		/*if (UBaseFunctionLibrary::IstargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
		*/
	}
}

void AWWWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GetInstigator 이벤트를 발생시킨 포인터 누가 데미지를 입혔는가 T클래스 반환(주체대상)
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		/*
		//피아식별을 하여 타겟이 아군이 아닐경우 전달
		if (UBaseFunctionLibrary::IstargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
		*/
	}
}
