// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "CustomPlayerController.h"
#include "Damageable.h"
#include "Engine/World.h"

void ARangedWeapon::Attack()
{
	// Implement the attack logic here
	UE_LOG(LogTemp, Log, TEXT("Attack"));
}

void ARangedWeapon::TryAttack(FVector ShootDirection)
{
	if(CurrentAmmoInMag<=0)
	{
		Reload();
		return;
	}
	
	FHitResult HitResult;
	// FVector StartLocation = PlayerOwner->GetPawn()->GetActorLocation();
	FVector StartLocation = GetActorLocation();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	}
	FVector MouseLocation = HitResult.Location;
	//FVector EndLocation = MouseLocation;
	FVector EndLocation = StartLocation + (ShootDirection * 1000.0f); // Adjust the range as needed
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the weapon itself

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	//Draw the raycast for debugging
	DrawDebugLine(GetWorld(), StartLocation, HitResult.Location, FColor::Red, false, 1.0f, 0, 1.0f);
	
	if (bHit)
	{
		// Process the hit result, e.g., apply damage to the hit actor
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// Apply damage or other effects to the hit actor
			if(HitActor->Implements<UDamageable>())
			{
				IDamageable::Execute_TakeDamage(HitActor, Damage);
				if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Damaged %s"), *HitActor->GetName())); }
			} else
			{
				if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit %s"), *HitActor->GetName())); }
			}
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
	//Super::OnPickUp_Implementation(player);
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Ranged weapon pickup"))); }
	// add the weapon to the player's inventory or equip it
	if(!pickedUp)
		player->SetWeapon(this);
	pickedUp = true;
}

void ARangedWeapon::OnDrop_Implementation(ACustomPlayerController* player) {
	// Implement the drop logic here
	UE_LOG(LogTemp, Log, TEXT("Dropped ranged weapon"));
	// remove the weapon from the player's inventory or unequip it
	pickedUp = false;
	//this.parent = nullptr;
}