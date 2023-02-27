// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/PacManHUD.h"
#include "../PacManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Public/PlayerPacMan.h"
#include "Engine/Canvas.h"

void APacManHUD::DrawHUD()
{
    APacManGameModeBase* GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
    
    switch(GameMode->GetGameState())
    {
        case EGameState::Menu:
        {
            DrawText(TEXT("Welcom to PacMan!!! \n\n N to start the game \n\n P to Pause the game"), FColor::White, (Canvas->SizeX / 3.5f), (Canvas->SizeY / 3.5f), HUDFont, 3.0f);
        }
        break;
        case EGameState::Playing:
        {
            APlayerPacMan* Player = Cast<APlayerPacMan>(UGameplayStatics::GetPlayerPawn(this, 0));
            if(Player)
            {
                FString LivesString = FString("Lives : ") + FString::FromInt(Player->GetLives());
                DrawText(LivesString, FColor::Green, 50, 50, HUDFont, 1.5f);

                FString CollectablesString = FString("Remaining Collectables") + FString::FromInt(Player->GetCollectablesToEat());
                DrawText(CollectablesString, FColor::Green, (Canvas->SizeX - 270), 50, HUDFont, 1.5f);
            }
        }
        break;
        case EGameState::Pause:
        {
            DrawText(TEXT("\n\n P to Pause the game \n\n"), FColor::White, (Canvas->SizeX / 3.5f), (Canvas->SizeY / 3.5f), HUDFont, 3.0f);
        }
        break;
        case EGameState::Win:
        {
            DrawText(TEXT("\n\n        You win! \n\n"), FColor::Red, (Canvas->SizeX / 3.5f), (Canvas->SizeY / 3.5f), HUDFont, 3.0f);
        }
        break;
        case EGameState::GameOver:
        {
            DrawText(TEXT("\n\n        You lose! \n\n"), FColor::Red, (Canvas->SizeX / 3.5f), (Canvas->SizeY / 3.5f), HUDFont, 3.0f);
        }
        break;
        default: break;
    }
}

