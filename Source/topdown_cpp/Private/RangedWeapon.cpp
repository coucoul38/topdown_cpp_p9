// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

void ARangedWeapon::Attack()
{
	// Implement the attack logic here
	UE_LOG(LogTemp, Log, TEXT("Attack"));
}

void ARangedWeapon::TryAttack(FVector ShootDirection)
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

void ARangedWeapon::Shoot()
{
	CurrentAmmoInMag -= 1;
}

void ARangedWeapon::Reload()
{
	CurrentAmmoInMag = MagSize;
}


void ARangedWeapon::OnPickUp_Implementation(ACustomPlayerController* player) {
	// Implement the pick-up logic here
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Ranged weapon pickup"))); }
	// add the weapon to the player's inventory or equip it
	pickedUp = true;
}

void ARangedWeapon::OnDrop_Implementation(ACustomPlayerController* player) {
	// Implement the drop logic here
	UE_LOG(LogTemp, Log, TEXT("Dropped ranged weapon"));
	// remove the weapon from the player's inventory or unequip it
	pickedUp = false;
	//this.parent = nullptr;
}