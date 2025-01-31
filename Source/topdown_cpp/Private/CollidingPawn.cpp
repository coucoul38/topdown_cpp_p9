#include "CollidingPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

// Constructor
ACollidingPawn::ACollidingPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    //SetActorEnableCollision(false);
    SetActorEnableCollision(ECollisionEnabled::QueryOnly);

    isActive = false;
    

    /*BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);*/

    // Create root component
    UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapArea"));
    //RootComponent = BoxComponent;
    BoxComponent->InitBoxExtent(FVector(42.f, 42.f, 42.f));
    BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
    BoxComponent->SetupAttachment(RootComponent);

    // Bind events
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollidingPawn::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACollidingPawn::OnOverlapEnd);

    // Create and set up mesh component
    UStaticMeshComponent* BoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    BoxVisual->SetupAttachment(BoxComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    if (BoxVisualAsset.Succeeded())
    {
        BoxVisual->SetStaticMesh(BoxVisualAsset.Object);
        BoxVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -42.0f));
        BoxVisual->SetWorldScale3D(FVector(1.f));
        BoxVisual->SetCollisionProfileName(TEXT("NoCollision"));
    }
}

void ACollidingPawn::BeginPlay() {
    Super::BeginPlay();

}

// Overlap Begin
void ACollidingPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        // Logs to the Output Log
        if (GEngine)
        {
            // Logs to the screen
            GEngine->AddOnScreenDebugMessage(
                -1, /* Unique key for this message (-1 means it will create a new message) */
                5.0f, /* Duration in seconds */
                FColor::Yellow, /* Message color */
                FString::Printf(TEXT("Overlap Begin with: %s"), *OtherActor->GetName())
            );
        }

        isActive = true;
    }
}

// Overlap End
void ACollidingPawn::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this))
    {
        // Logs to the Output Log
        if (GEngine)
        {
            

            // Logs to the screen
            GEngine->AddOnScreenDebugMessage(
                -1, /* Unique key for this message (-1 means it will create a new message) */
                5.0f, /* Duration in seconds */
                FColor::Yellow, /* Message color */
                FString::Printf(TEXT("Overlap End with: %s"), *OtherActor->GetName())
            );
        }

        isActive = false;
    }
}

// Tick
void ACollidingPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}