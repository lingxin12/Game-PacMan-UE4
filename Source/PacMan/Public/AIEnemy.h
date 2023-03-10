// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "../PacManGameModeBase.h"
#include "AIEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()

public:
    void OnPossess(APawn* InPawn) override;
    virtual void  OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

    void SearchNewPoint();

    void GoHome();
    void ReArm();
    void StopMove();

private:
    AEnemy* Bot;
    FVector HomeLocation;
    FTimerHandle TimerHandle;
    APacManGameModeBase* GameMode;
};
