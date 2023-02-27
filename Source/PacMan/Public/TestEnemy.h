// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TestEnemy.generated.h"

UCLASS()
class PACMAN_API ATestEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    bool IsDead() { return bIsDead; }

    void SetVulnerable();
    void SetInVulnerable();

    void SetMove(bool MoveIt);
    void Killed();
    void ReArm();

    void TestMove();

    UFUNCTION()
    void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    UPROPERTY(VisibleAnywhere, Category = "Body")
    UStaticMeshComponent* EnemyBody;

    UMaterialInterface* DefaultMaterial;
    UMaterialInterface* VulnerableMaterial;
    FTimerHandle TimerHandle;
    bool bIsVulnerable;
    bool bIsDead;
};
