#include "EnemyAI.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/Engine.h"

// Sets default values
AEnemyAI::AEnemyAI()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // Create Perception Component
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

    // Create and configure sight sense
    UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 1000.0f;
    SightConfig->LoseSightRadius = 1200.0f;
    SightConfig->PeripheralVisionAngleDegrees = 30.0f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    // Create and configure hearing sense
    UAISenseConfig_Hearing* HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
    HearingConfig->HearingRange = 1500.0f;
    HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
    HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
    HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

    // Add senses to perception component
    PerceptionComponent->ConfigureSense(*SightConfig);
    PerceptionComponent->ConfigureSense(*HearingConfig);
    PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

    // Bind the perception update event
    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAI::OnTargetPerceptionUpdated);
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
    Super::BeginPlay();

    SetPatrolPoints();
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyAI::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            if (UBlackboardComponent* BlackboardComp = GetBlackboardComponent())
            {
                BlackboardComp->SetValueAsObject(TEXT("TargetActorSight"), Actor);
            }
        }
        else
        {
            if (UBlackboardComponent* BlackboardComp = GetBlackboardComponent())
            {
                //get the last known location of the target
                FVector TargetLocation = Stimulus.StimulusLocation;
                BlackboardComp->ClearValue(TEXT("TargetActorSight"));
                BlackboardComp->SetValueAsVector(TEXT("TargetLocationSight"), TargetLocation);
                BlackboardComp->SetValueAsBool(TEXT("HasLooseSight"), true);
            }
        }
    }
    else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
    {
        
    }
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Perception Updated: %s"), *Actor->GetName()));
    }
}

UBlackboardComponent* AEnemyAI::GetBlackboardComponent() const
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        return AIController->GetBlackboardComponent();
    }
    return nullptr;
}

TArray<FVector> AEnemyAI::GetPatrolPoints()
{
    return PatrolPointsWorld;
}

void AEnemyAI::SetPatrolPoints()
{
    for (const FVector& LocalPoint : PatrolPoints)
    {
        PatrolPointsWorld.Add(GetActorTransform().TransformPosition(LocalPoint));
    }
}

void AEnemyAI::TakeDamage_Implementation(int Damage)
{
    IDamageable::TakeDamage_Implementation(Damage);
    if(Damage <= 0)
    {
        return;
    }
    CurrentHealth -= Damage;
    if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("took damage")));};
}

void AEnemyAI::Heal_Implementation(int HealAmount)
{
    IDamageable::Heal_Implementation(HealAmount);
    if(HealAmount <= 0)
    {
        return;
    }
    CurrentHealth += HealAmount;
}
