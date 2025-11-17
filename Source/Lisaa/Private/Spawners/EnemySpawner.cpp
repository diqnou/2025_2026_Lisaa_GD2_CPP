#include "Spawners/EnemySpawner.h"
#include "Characters/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	// Check si le timer est supérieur à 0 et si all enemy classes n'est pas vide
	if (SpawnInterval > 0.f && AllEnemyClasses.Num() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this,
			&AEnemySpawner::SpawnTick, SpawnInterval, true);
	}
}

void AEnemySpawner::SpawnTick()
{
	if (bScaleOverTime)
	{
		const float Time = GetWorld()->GetTimeSeconds();
		const int32 Bonus = FMath::FloorToInt(Time / 30.f);
		MaxAlive = FMath::Clamp(MaxAlive + Bonus, MaxAlive, 200.f);
	}

	for (int32 IndexAlive = AllEnemyAlive.Num() - 1; IndexAlive >= 0; --IndexAlive)
		if (!AllEnemyAlive[IndexAlive].IsValid())
			AllEnemyAlive.RemoveAt(IndexAlive);

	if (GetAliveCount() >= MaxAlive)
		return;

	TSubclassOf<AEnemyCharacter> EnemyClassToSpawn = PickEnemyClass();
	if (!EnemyClassToSpawn) return;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector SpawnLocation = PickSpawnPointAroundPlayer();

	AEnemyCharacter* EnemyToSpawn = GetWorld()->SpawnActor<AEnemyCharacter>(
		EnemyClassToSpawn,
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParameters);

	if (EnemyToSpawn)
	{
		AllEnemyAlive.Add(EnemyToSpawn);
		
	}
	
	
}

int32 AEnemySpawner::GetAliveCount()
{
	int32 CurrentAliveCount = 0;
	for (auto& IndexEnemy : AllEnemyAlive)
	{
		if (IndexEnemy.IsValid())
		{
			CurrentAliveCount++;
		}
	}
	return CurrentAliveCount;
}

FVector AEnemySpawner::PickSpawnPointAroundPlayer() const
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	const FVector Center = PlayerPawn ? PlayerPawn->GetActorLocation() : GetActorLocation();

	const float Angle = FMath::RandRange(0.f, 2*PI);
	const FVector Offset(FMath::Cos(Angle) * SpawnRadius, FMath::Sin(Angle) * SpawnRadius, 0.f);
	
	return Center + Offset;
}

TSubclassOf<AEnemyCharacter> AEnemySpawner::PickEnemyClass() const
{
	if (AllEnemyClasses.Num() == 0) return nullptr;

	if (TypeWeights.Num() != AllEnemyClasses.Num() || TypeWeights.Num() == 0)
	{
		const int32 IndexEnemy = FMath::RandRange(0, AllEnemyClasses.Num() - 1);
		return AllEnemyClasses[IndexEnemy];
	}

	int32 Total = 0;
	for (int32 IndexWeights : TypeWeights)
		Total += FMath::Max(0, IndexWeights);

	if (Total <= 0)
		return AllEnemyClasses[FMath::RandRange(0, AllEnemyClasses.Num() - 1)];

	int32 RandomWeight = FMath::RandRange(1, Total);
	int32 Accuracy = 0;
	for (int32 Index = 0; Index < AllEnemyClasses.Num(); ++Index)
	{
		Accuracy += FMath::Max(0, TypeWeights[Index]);
		if (RandomWeight <= Accuracy)
			return AllEnemyClasses[Index];
	}
	return AllEnemyClasses.Last();
}

