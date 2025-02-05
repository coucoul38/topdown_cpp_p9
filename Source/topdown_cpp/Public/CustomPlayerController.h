// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "WeaponComponent.h"
#include "PickableObject.h"

#include "CustomPlayerController.generated.h"



UCLASS()
class TOPDOWN_CPP_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	ACustomPlayerController();
	void Tick(float DeltaSeconds);
	FHitResult ShootRaycast();

	AActor* lastPickableObject;
	void CheckPickupObject(FHitResult HitResult);
	void RotatePlayerToMouse(FHitResult HitResult);

	AWeaponComponent* weaponComponent;

protected:
	virtual void SetupInputComponent() override;
	void TryAttack(const FInputActionValue& Value);
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* WeaponMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY()
	AWeaponComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int PickupDistance = 100;

	UPROPERTY()
	FVector PlayerDirection;

	UFUNCTION()
	void DropWeapon();

	void WhenMoveInput(const FInputActionValue& Value);

	void Interact();
};
