// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"

#include <string>

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "PickableObject.h"
#include "Engine/LocalPlayer.h"

ACustomPlayerController::ACustomPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ACustomPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FHitResult hit = ShootRaycast();
	RotatePlayerToMouse(hit);
	CheckPickupObject(hit);
}

FHitResult ACustomPlayerController::ShootRaycast() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	return HitResult;
}

void ACustomPlayerController::RotatePlayerToMouse(FHitResult HitResult)
{
	if (HitResult.bBlockingHit)
	{
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			FVector MouseLocation = HitResult.ImpactPoint;
			FVector PawnLocation = ControlledPawn->GetActorLocation();
			PlayerDirection = MouseLocation - PawnLocation;
			PlayerDirection.Z = 0.0f; // Keep the rotation in the XY plane

			FRotator NewRotation = PlayerDirection.Rotation();
			ControlledPawn->SetActorRotation(NewRotation);
		}
	}
}

void ACustomPlayerController::CheckPickupObject(FHitResult HitResult) {
	if (HitResult.bBlockingHit)
	{
		// If hitting a different object, remove outline from last one
		if (lastPickableObject != nullptr) {
			if ((HitResult.Location - GetPawn()->GetActorLocation()).Length() >= PickupDistance || lastPickableObject != HitResult.GetActor()) {
				TArray<USceneComponent*> ChildrenComponents;
				lastPickableObject->GetRootComponent()->GetChildrenComponents(true, ChildrenComponents);
				for (USceneComponent* ChildComponent : ChildrenComponents)
				{
					if (UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(ChildComponent))
					{
						// Enable Custom Depth for the component
						PrimitiveComp->SetRenderCustomDepth(false);
					}
				}
				lastPickableObject = nullptr;
			}
		}

		if (Cast<IPickableObject>(HitResult.GetActor())) {
			if ((HitResult.Location - GetPawn()->GetActorLocation()).Length() < PickupDistance)
			{
				// store object
				lastPickableObject = HitResult.GetActor();

				// set outline on object
				TArray<USceneComponent*> ChildrenComponents;
				HitResult.GetComponent()->GetChildrenComponents(true, ChildrenComponents);

				for (USceneComponent* ChildComponent : ChildrenComponents)
				{
					if (UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(ChildComponent))
					{
						// Enable Custom Depth for the component
						PrimitiveComp->SetRenderCustomDepth(true);
					}
				}
			}
		}
	}
}

void ACustomPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 1);
		Subsystem->AddMappingContext(WeaponMappingContext,0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::WhenMoveInput); 
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ACustomPlayerController::TryAttack);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACustomPlayerController::Interact);
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Binded Action"))); }
	}
	else
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this))); }
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACustomPlayerController::TryAttack(const FInputActionValue& Value)
{
	if (Weapon != nullptr)
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Shoot"))); }
		Weapon->TryAttack(PlayerDirection);
	}

	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Shoot"))); }
	
	FHitResult HitResult;
	APawn* ControlledPawn = GetPawn();
	FVector StartLocation = ControlledPawn->GetActorLocation();
	FVector EndLocation = StartLocation + (PlayerDirection * 1000.0f); // Adjust the range as needed

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the weapon itself

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	
	// Draw the raycast for debugging
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1.0f, 0, 1.0f);
	
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

void ACustomPlayerController::Interact() {
	if (lastPickableObject != nullptr) {
		if(lastPickableObject->Implements<UPickableObject>())
		{
			IPickableObject::Execute_OnPickUp(lastPickableObject, this);
			if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Object implements interface"))); }
		} else
		{
			if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Object doesn't implement pickable object interface"))); }
		}
	}
}

void ACustomPlayerController::DropWeapon()
{
	if (Weapon != nullptr)
	{
		Weapon = nullptr;
	}
}

void ACustomPlayerController::WhenMoveInput(const FInputActionValue& Value)
{
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("MoveInput"))); }
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		FVector WorldDirection = FVector(MovementVector.X, MovementVector.Y, 0.f);
		ControlledPawn->AddMovementInput(WorldDirection, 1.0f, false);
	}
}