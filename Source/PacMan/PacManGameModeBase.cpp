// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "PacManGameModeBase.h"

void  APacManGameModeBase::BeginPlay()
{
    SetGameState(EGameState::Menu);

    for(TActorIterator<AEnemy> EnemyIterator(GetWorld()); EnemyIterator; ++ EnemyIterator)
    {
        AEnemy* TempEnemy = Cast<AEnemy>(*EnemyIterator);
        Enemys.Add(TempEnemy);
    }
}

void APacManGameModeBase::SetGameState(EGameState Value)
{
    // UE_LOG(LogTemp, Warning, TEXT("enter gamemode base setgamestate()"));
    GameState = Value;
    switch(GameState)
    {
        case EGameState::Menu:
        break;
        case EGameState::Playing:
        {
            for(auto& Enemy: Enemys)
            {
                Enemy->SetMove(true);
            }
        }
        break;
        case EGameState::Pause:
        {
            for(auto& Enemy: Enemys)
            {
                Enemy->SetMove(false);
            }
        }
        break;
        case EGameState::Win:
        {
            for(auto& Enemy: Enemys)
            {
                Enemy->Destroy();
            }
        }
        break;
        case EGameState::GameOver:
        {
            for(auto& Enemy: Enemys)
            {
                Enemy->Destroy();
            }
        }
        break;
        default: break;
    }
}

void APacManGameModeBase::SetEnemyVulnerable()
{
    for(auto& Enemy: Enemys)
    {
        Enemy->SetVulnerable();
    }
}