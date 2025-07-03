// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Controller/WWAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Common/WWDebugHelper.h"
#include "Common/PlayerControllers/WWPlayerController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AWWAIController::AWWAIController(const FObjectInitializer& ObjectInitializer)
{
	//SetDefaultSubobjectClass로 CrowdFollowingComponent 사용
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdFollowingComponent Valid"), FColor::Green);
	}

	//AISenseConfig_Sight 생성자
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

	//적 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;

	//아군 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;

	//중립 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	//시아 반경 설정
	AISenseConfig_Sight->SightRadius = 5000.0f;

	//대상을 잃는 시아 설정
	AISenseConfig_Sight->LoseSightRadius = 0.f;

	//주변 시아각
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.0f;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	//센서설정
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AWWAIController::OnEnemyPerceptionUpdated);

	//팀 아이디 부여
	SetGenericTeamId(FGenericTeamId(1));
}

void AWWAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//Debug::Print(FString::Printf(TEXT("Perception Updated : %s"), *Actor->GetName()), FColor::Green);
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			// TargetActor설정
			if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
			{
				BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
			}
		}
	}
}

ETeamAttitude::Type AWWAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

	// 팀 아이디가 낮은 팀만 공격(필요시 변경)
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}
		
	return ETeamAttitude::Friendly;
}

void AWWAIController::BeginPlay()
{
	Super::BeginPlay();
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdFollowingComponent->SetCrowdSimulationState(bDetourCrowdAvoidence
			                                                 ? ECrowdSimulationState::Enabled
			                                                 : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidenceQuality)
		{
		case 1: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4: CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			break;
		}

		CrowdFollowingComponent->SetAvoidanceGroup(1);
		CrowdFollowingComponent->SetGroupsToAvoid(1);
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}
