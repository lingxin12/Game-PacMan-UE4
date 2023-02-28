// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AIEnemy.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"

void AAIEnemy::OnPossess(APawn* InPawn)
{
    // UE_LOG(LogTemp, Warning, TEXT("OnPossess()"));
    Super::OnPossess(InPawn);
    Bot = Cast<AEnemy>(InPawn);
    GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));

    HomeLocation = Bot->GetActorLocation();
    SearchNewPoint();
}


void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if(!Bot->IsDead() && GameMode->GetGameState() != EGameState::Pause)
    {
        SearchNewPoint();
    }
}

void AAIEnemy::SearchNewPoint()
{
    UNavigationSystemV1* NavigationMesh = UNavigationSystemV1::GetCurrent(this);

    if(NavigationMesh)
    {
        const float SearchRadius = 10000.0f;
        FNavLocation RandomPt;

        const bool bFound = NavigationMesh->GetRandomReachablePointInRadius(Bot->GetActorLocation(), SearchRadius, RandomPt);
        if(bFound)
        {
            // UE_LOG(LogTemp, Warning, TEXT("Set new Point : %s"), *RandomPt.Location.ToString());
            MoveToLocation(RandomPt);
        }
    }
}

void AAIEnemy::GoHome()
{
    // MoveToLocation(HomeLocation);
    Bot->SetActorLocation(HomeLocation); // 1.1
    MoveToLocation(HomeLocation);
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AAIEnemy::ReArm, 5.0f, false);
}

void AAIEnemy::ReArm()
{
    GetWorldTimerManager().ClearTimer(TimerHandle);
    Bot->ReArm();
}

void AAIEnemy::StopMove()
{
    MoveToLocation(Bot->GetActorLocation());
}