// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "CustomPlayerController.h"
// forward declaration
class ACustomPlayerController;

#include "PickableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPickableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWN_CPP_API IPickableObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickable")
	void OnPickUp(ACustomPlayerController* player);
};
