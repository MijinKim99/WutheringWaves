// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AI/Task/BTTask_RotateToFaceTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget()
{
	NodeName = TEXT("Native Rotate To FaceTarget");
	AnglePrecision = 10.0f;
	RotationInterpSpeed = 5.0f;

	//노티파이 틱 비활성화
	bNotifyTick = false;

	//태스크 완료시 호출하도록 처리
	bNotifyTaskFinished = true;

	//생성한 노드는 인스턴스화 시키지 않는다.(변수값을 저장을 못하지만 다른 방법을 통해 운용)
	bCreateNodeInstance = false;

	INIT_TASK_NODE_NOTIFY_FLAGS();

	TagetFaceKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, TagetFaceKey), AActor::StaticClass());
	
}

void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		TagetFaceKey.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const
{
	//메모리에 할당
	return sizeof(FRotateToFaceTagetTaskMemory);
}

FString UBTTask_RotateToFaceTarget::GetStaticDescription() const
{
	const FString KeyDescription = TagetFaceKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("Rotate to FaceTarget key : %s, angle precision : %s"),
		*KeyDescription, *FString::SanitizeFloat(AnglePrecision));
}

EBTNodeResult::Type UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TagetFaceKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	//AIC에 Pawn
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	//메모리 인스턴스화
	FRotateToFaceTagetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTagetTaskMemory>(NodeMemory);

	check(Memory);

	Memory->OwningPawn = OwningPawn;
	Memory->TargetActor = TargetActor;

	if (!Memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}

	if (HasAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	return EBTNodeResult::InProgress;
}

void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	FRotateToFaceTagetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTagetTaskMemory>(NodeMemory);

	if (!Memory->IsValid())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (HasAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Memory->OwningPawn->GetActorLocation(), Memory->TargetActor->GetActorLocation());
		const FRotator TagetRot = FMath::RInterpTo(Memory->OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);
		Memory->OwningPawn->SetActorRotation(TagetRot);
	}
}

bool UBTTask_RotateToFaceTarget::HasAnglePrecision(APawn* QueryPawn, AActor* TargetActor)
{
	const FVector OwnerForward = QueryPawn->GetActorForwardVector();
	const FVector OwnerToTargetNormalized = (TargetActor->GetActorLocation() - QueryPawn->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(OwnerForward, OwnerToTargetNormalized);
	const float AngleDiff = UKismetMathLibrary::DegAcos(DotResult);

	return AngleDiff <= AnglePrecision;
}