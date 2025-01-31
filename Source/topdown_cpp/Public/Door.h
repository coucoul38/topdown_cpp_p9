// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollidingPawn.h"
#include "Door.generated.h"

UCLASS()
class TOPDOWN_CPP_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool open;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	TArray<ACollidingPawn*> PressurePlates = {};

	UFUNCTION()
	virtual void Open();
	UFUNCTION()
	virtual void Close();
};
