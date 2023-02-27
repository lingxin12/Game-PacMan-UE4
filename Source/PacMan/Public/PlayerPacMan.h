// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Collectables.h"
#include "Components/CapsuleComponent.h"
#include "EngineUtils.h"
#include "PlayerPacMan.generated.h"

UCLASS()
class PACMAN_API APlayerPacMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerPacMan();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveXAxis(float AxisValue);
    void MoveYAxis(float AxisValue);

    UFUNCTION()
    void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    int32 GetLives() const { return Lives; }
    int32 GetCollectablesToEat() const { return CollectablesToEat; }

    void GameModeRestart();
    void GameModeNewGame();
    void GameModePause();

    void Killed();

    FString Gss[5] = {TEXT("Menu"), TEXT("Playing"), TEXT("Pause"), TEXT("Win"), TEXT("GameOver")};

private:
    FVector CurrentVelocity;
    APacManGameModeBase* GameMode;

    int32 CollectablesToEat;
    int32 Lives;
    FVector StartPoint;
};
