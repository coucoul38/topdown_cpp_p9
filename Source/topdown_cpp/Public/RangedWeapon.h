// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "PickableObject.h"
#include "RangedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_CPP_API ARangedWeapon : public AWeaponComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int MagSize;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	int CurrentAmmoInMag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool IsAutomatic;

	bool IsReloading;

	virtual void Attack() override;

	virtual void TryAttack(FVector ShootDirection) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Reload();

	// Implemented from IPickableObject
	virtual void OnPickUp_Implementation(ACustomPlayerController* player) override;
	virtual void OnDrop_Implementation(ACustomPlayerController* player) override;
};
