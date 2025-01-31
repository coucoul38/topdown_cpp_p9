// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	}
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	destination = Points[0];
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = destination.GetLocation() - GetActorLocation();
	// move in dir
	dir.Normalize();
	SetActorLocation(GetActorLocation() + dir * Speed * DeltaTime);
	

	// move towards destination
	//SetActorLocation(FMath::Lerp(GetActorLocation(), destination.GetLocation(), Speed / 100));
	//SetActorLocation(FMath::VInterpTo(GetActorLocation(), destination.GetLocation(), DeltaTime, Speed/100));
	CheckArrived();
}

void AMovingPlatform::CheckArrived()
{
	// Check if the platform has arrived at the destination
	if (FVector::Dist(GetActorLocation(), destination.GetLocation()) < 10)
	{
		// Set the next destination
		if (currentDestIndex == Points.Num() - 1)
		{
			currentDestIndex = 0;
		}
		else
		{
			currentDestIndex++;
		}
		destination = Points[currentDestIndex];


		// Logs to the Output Log
		if (GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Current destIndex: %d"), currentDestIndex));}
	}
}
