// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EngineUtils.h"
#include "Public/Enemy.h"
#include "PacManGameModeBase.generated.h"

/**
 * 
 */

enum class EGameState: uint8
{
    Menu,
    Playing,
    Pause,
    Win,
    GameOver
};

UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    EGameState GetGameState() const { return GameState; }
    void SetGameState(EGameState Value);

    void SetEnemyVulnerable();

private:
    EGameState GameState;
    TArray<class AEnemy*> Enemys;
};
