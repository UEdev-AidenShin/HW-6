#include "Donut.h"

ADonut::ADonut()
{
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Shapes/Shape_Torus.Shape_Torus"));
    if (MeshAsset.Succeeded())
    {
        StaticMeshComp->SetStaticMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile"));
    if (MaterialAsset.Succeeded())
    {
        StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
    }

    PrimaryActorTick.bCanEverTick = true;
    MoveSpeed = 40.0f;
    MaxRange = 50.0f;
}


void ADonut::BeginPlay()
{
    Super::BeginPlay();

    // 타이머 설정
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(ChangeMeshTimerHandle, this, &ADonut::ChangeMesh, 2.0f, true);
        GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ADonut::DestroyActor, 10.0f, true);
    }

    StartLocation = GetActorLocation();
    MoveDirection = 1;
}



void ADonut::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!FMath::IsNearlyZero(MoveSpeed))
    {
        FVector CurrentLocation = GetActorLocation();

        FVector NewLocation = CurrentLocation + FVector(0.0f, 0.0f, MoveDirection * MoveSpeed * DeltaTime);

        if (NewLocation.Z >= StartLocation.Z + MaxRange) 
        {
            NewLocation.Z = StartLocation.Z + MaxRange; 
            MoveDirection = -1; 
        }
        else if (NewLocation.Z <= StartLocation.Z - MaxRange)
        {
            NewLocation.Z = StartLocation.Z - MaxRange;
            MoveDirection = 1;
        }

        SetActorLocation(NewLocation);
    }
}

void ADonut::ChangeMesh()
{
    // 메시 변경 로직 추가
}

void ADonut::ResetActorPosition()
{
    SetActorLocation(FVector::ZeroVector);
}

float ADonut::GetRotationSpeed() const
{
    return MoveSpeed;
}

void ADonut::DestroyActor()
{
    Destroy();
}