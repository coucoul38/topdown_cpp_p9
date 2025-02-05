#include "BTTaskPatrol.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyAI.h"

UBTTaskPatrol::UBTTaskPatrol()
{
	NodeName = "Patrol";
}

EBTNodeResult::Type UBTTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AEnemyAI* EnemyAI = Cast<AEnemyAI>(AIController->GetPawn());
		if (EnemyAI)
		{
			TArray<FVector> PatrolPoints = EnemyAI->GetPatrolPoints();
			if (PatrolPoints.Num() > 0)
			{
				UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
				if (BlackboardComp)
				{
					int32 PatrolIndex = BlackboardComp->GetValueAsInt(PatrolIndexKey.SelectedKeyName);
					PatrolIndex = (PatrolIndex + 1) % PatrolPoints.Num();
					FVector PatrolLocation = PatrolPoints[PatrolIndex];

					BlackboardComp->SetValueAsVector(PatrolLocationKey.SelectedKeyName, PatrolLocation);
					BlackboardComp->SetValueAsInt(PatrolIndexKey.SelectedKeyName, PatrolIndex);

					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Patrol Location: %s"), *PatrolLocation.ToString()));
					}
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}