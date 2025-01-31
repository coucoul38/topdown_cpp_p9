 // Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	open = false;

	// Create root component
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapArea"));
	//RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(42.f, 42.f, 42.f));
	BoxComponent->SetupAttachment(RootComponent);

	// Create and set up mesh component
	UStaticMeshComponent* BoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	BoxVisual->SetupAttachment(BoxComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (BoxVisualAsset.Succeeded())
	{
		BoxVisual->SetStaticMesh(BoxVisualAsset.Object);
		BoxVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -42.0f));
		BoxVisual->SetWorldScale3D(FVector(1.f));
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (ACollidingPawn* Actor : PressurePlates)
	{
		if (Actor->isActive) {
			Open();
		}
	}
}

void ADoor::Open() {
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Door Open")));
	}
}

void ADoor::Close() {
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Door Close")));
	}
}