#include "EnemySpawner.h"
#include "Characters/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"


AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnDelay > 0.0f && AllDifferentEnemyClasses.Num() > 0)
	{
		GetWorld() -> GetTimerManager().SetTimer(SpawnTimerHandle, this,
			&AEnemySpawner::SpawnTick, SpawnDelay, true);
	}
}

int32 AEnemySpawner::GetAliveCount()
{
	int32 CurrentAliveCount = 0;
	for (auto&IndexEnemy : AllEnemiesAlive)
	{
		if (IndexEnemy.IsValid() )
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

	const float Angle = FMath ::RandRange(0.f, 2*PI);
	const FVector Offset(FMath ::Cos(Angle) * SpawnRadius, FMath ::Sin(Angle) * SpawnRadius, 0.f);

	return Center + Offset;
}

TSubclassOf<AEnemyCharacter> AEnemySpawner::PickEnemyClass() const
{
	if (AllDifferentEnemyClasses.Num() == 0) return nullptr;

	if (TypeWeights.Num() != AllDifferentEnemyClasses.Num() || TypeWeights.Num() == 0)
	{
		const int32 IndexEnemy= FMath::RandRange(0, AllDifferentEnemyClasses.Num() -1);
		return AllDifferentEnemyClasses[IndexEnemy];
	}

	int32 Total = 0;
	for (int32 IndexWeights : TypeWeights)
		Total += FMath::Max(0, IndexWeights);

	if (Total <= 0)
		return AllDifferentEnemyClasses[FMath::RandRange(0, AllDifferentEnemyClasses.Num()-1)];

	int32 RandomWeight = FMath::RandRange(1, Total);
	int32 Accuracy = 0;
	for (int32 Index = 0; Index < AllDifferentEnemyClasses.Num(); ++Index)
	{
		Accuracy += FMath::Max(0,TypeWeights[Index]);
		if (RandomWeight <= Accuracy)
			return AllDifferentEnemyClasses[Index];
	}
	return AllDifferentEnemyClasses.Last();
}

void AEnemySpawner::SpawnTick()
{
	if (bScaleOverTime)
	{
		const float Time = GetWorld()->GetTimeSeconds();
		const int32 Bonus = FMath:: FloorToInt(Time / 30.f);
		MaxEnemiesAlive = FMath::Clamp(MaxEnemiesAlive + Bonus, MaxEnemiesAlive, 200.f);
	}

	for (int32 IndexAlive = AllEnemiesAlive.Num() -1; IndexAlive >= 0; --IndexAlive)
		if (!AllEnemiesAlive[IndexAlive].IsValid())
			AllEnemiesAlive.RemoveAt(IndexAlive);

	if (GetAliveCount() >= MaxEnemiesAlive)
		return;

	TSubclassOf<AEnemyCharacter> EnemyClassToSpawn = PickEnemyClass();
	if (!EnemyClassToSpawn) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector SpawnLocation = PickSpawnPointAroundPlayer();


	AEnemyCharacter* EnemyToSpawn = GetWorld() -> SpawnActor<AEnemyCharacter>(
		EnemyClassToSpawn,SpawnLocation, FRotator ::ZeroRotator, SpawnParams);

	if (EnemyToSpawn)
	{
		AllEnemiesAlive.Add(EnemyToSpawn);
	}
	

}


