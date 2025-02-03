// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponComponent.generated.h"

UCLASS()
class TOPDOWN_CPP_API AWeaponComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float SpeedModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Attack();
	
	virtual void TryAttack(FVector ShootDirection);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual float GetSpeedModifier();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual float GetAttackCooldown();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual float GetDamage();
};
