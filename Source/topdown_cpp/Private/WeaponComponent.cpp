// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

// Sets default values
AWeaponComponent::AWeaponComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponComponent::Attack()
{
}

void AWeaponComponent::TryAttack(FVector ShootDirection)
{
	FHitResult HitResult;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + (ShootDirection * 1000.0f); // Adjust the range as needed

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the weapon itself

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		// Process the hit result, e.g., apply damage to the hit actor
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// Apply damage or other effects to the hit actor
			UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Missed"));
	}
}

//create a method call GetShootDirection that return the direction on the x and y axis at where the player click by taking as argument the

float AWeaponComponent::GetSpeedModifier()
{
	return SpeedModifier;
}

float AWeaponComponent::GetAttackCooldown()
{
	return AttackCooldown;
}

float AWeaponComponent::GetDamage()
{
	return Damage;
}

