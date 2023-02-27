// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Collectables.h"

// Sets default values
ACollectables::ACollectables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SetActorEnableCollision(true);
    CollectableComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
    BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionBase"));
    CollectableComponent->SetupAttachment(BaseCollisionComponent);
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if(Sphere.Succeeded()) {
        CollectableComponent->SetStaticMesh(Sphere.Object);
    }

    CollectableComponent->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
    BaseCollisionComponent->SetSphereRadius(16);
}

// Called when the game starts or when spawned
void ACollectables::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

