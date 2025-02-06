// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAI.generated.h"

UCLASS()
class TOPDOWN_CPP_API AEnemyAI : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int CurrentHealth = 100;
	
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* PerceptionComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UBlackboardComponent* GetBlackboardComponent() const;
	TArray<FVector> GetPatrolPoints();
	void SetPatrolPoints();

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (MakeEditWidget = true))
	TArray<FVector> PatrolPoints;
	
	TArray<FVector> PatrolPointsWorld;

	// Implement IDamageable interface
	virtual void TakeDamage_Implementation(int Damage) override;
	virtual void Heal_Implementation(int HealAmount) override;
};
