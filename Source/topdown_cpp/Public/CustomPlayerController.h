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

	IPickableObject* lastPickableObject;
	void CheckPickupObject(FHitResult HitResult);
	void RotatePlayerToMouse(FHitResult HitResult);

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

	UPROPERTY()
	AWeaponComponent* Weapon;

	UPROPERTY()
	FVector PlayerDirection;

	void WhenMoveInput(const FInputActionValue& Value);
};
