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