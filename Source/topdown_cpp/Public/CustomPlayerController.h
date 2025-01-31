// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "CustomPlayerController.generated.h"



UCLASS()
class TOPDOWN_CPP_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	ACustomPlayerController();
protected:
	virtual void SetupInputComponent() override;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	void WhenMoveInput(const FInputActionValue& Value);
};
