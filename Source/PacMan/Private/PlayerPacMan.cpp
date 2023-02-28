// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/PlayerPacMan.h"

// Sets default values
APlayerPacMan::APlayerPacMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPacMan::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
    PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerPacMan::OnCollision);

    Lives = 3;
    StartPoint = GetActorLocation();

    for(TActorIterator<ACollectables> ActorIterator(GetWorld()); ActorIterator; ++ ActorIterator)
    {
        ++ CollectablesToEat;
    }
}

// Called every frame
void APlayerPacMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("now gamemode is %s"), *Gss[int(GameMode->GetGameState())]);
}

// Called to bind functionality to input
void APlayerPacMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveX", this, &APlayerPacMan::MoveXAxis);
    PlayerInputComponent->BindAxis("MoveY", this, &APlayerPacMan::MoveYAxis);

    PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APlayerPacMan::GameModeNewGame);
    PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APlayerPacMan::GameModeRestart);
    PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerPacMan::GameModePause);

    PlayerInputComponent->BindAction("WTurnaround", IE_Pressed, this, &APlayerPacMan::WTurnaround);
    PlayerInputComponent->BindAction("STurnaround", IE_Pressed, this, &APlayerPacMan::STurnaround);
    PlayerInputComponent->BindAction("ATurnaround", IE_Pressed, this, &APlayerPacMan::ATurnaround);
    PlayerInputComponent->BindAction("DTurnaround", IE_Pressed, this, &APlayerPacMan::DTurnaround);
}

void APlayerPacMan::MoveXAxis(float AxisValue)
{
    if(GameMode->GetGameState() == EGameState::Playing)
    {
        CurrentVelocity.X = AxisValue;
        AddMovementInput(CurrentVelocity);
    }
}

void APlayerPacMan::MoveYAxis(float AxisValue)
{
    if(GameMode->GetGameState() == EGameState::Playing)
    {
        CurrentVelocity.Y = AxisValue;
        AddMovementInput(CurrentVelocity);
    }
}

void APlayerPacMan::GameModeRestart()
{
    GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));   
}

void APlayerPacMan::GameModeNewGame()
{
    if(GameMode->GetGameState() == EGameState::Menu)
    {
        GameMode->SetGameState(EGameState::Playing);
    }
}

void APlayerPacMan::GameModePause()
{
    if(GameMode->GetGameState() == EGameState::Playing)
    {
        GameMode->SetGameState(EGameState::Pause);
    }
    else if(GameMode->GetGameState() == EGameState::Pause)
    {
        GameMode->SetGameState(EGameState::Playing);
    }
}

void APlayerPacMan::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(GameMode->GetGameState() == EGameState::Playing && OtherActor->IsA(ACollectables::StaticClass()))
    {   
        ACollectables* Collectable = Cast<ACollectables>(OtherActor);

        if(Collectable->bIsSuperCollectable)
        {
            GameMode->SetEnemyVulnerable();
        }

        if(OtherActor->IsA(ACollectables::StaticClass()))
        {
            OtherActor->Destroy();
            if(-- CollectablesToEat <= 0)
            {
                GameMode->SetGameState(EGameState::Win);
            }
        }
    }
}

void APlayerPacMan::Killed()
{
    if(-- Lives <= 0)
    {
        GameMode->SetGameState(EGameState::GameOver);
    }
    else
    {
        SetActorLocation(StartPoint);
    }
}

void APlayerPacMan::WTurnaround()
{
    if(GameMode->GetGameState() == EGameState::Playing)
    {
        SetActorRotation(FRotator(0, -90, 0));
    }
}

void APlayerPacMan::STurnaround()
{
    if(GameMode->GetGameState() == EGameState::Playing)
    {
        SetActorRotation(FRotator(0, 90, 0));
    }
}

void APlayerPacMan::ATurnaround()
{
    if(GameMode->GetGameState() == EGameState::Playing)
    {
        SetActorRotation(FRotator(0, 180, 0));
    }
}

void APlayerPacMan::DTurnaround()
{
    if(GameMode->GetGameState() == EGameState::Playing)
    {
        SetActorRotation(FRotator(0, 0, 0));
    }
}