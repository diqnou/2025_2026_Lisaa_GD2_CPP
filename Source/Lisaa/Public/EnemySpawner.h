#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyCharacter;

UCLASS()

class LISAA_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	UPROPERTY(EditAnywhere,Category = "Spawner")
	TArray<TSubclassOf<AEnemyCharacter>> AllDifferentEnemyClasses;

	UPROPERTY(EditAnywhere,Category = "Spawner")
	float SpawnDelay = 1.0f;

	UPROPERTY(EditAnywhere,Category = "Spawner")
	int32 MaxEnemiesAlive = 50;

	UPROPERTY(EditAnywhere,Category = "Spawner")
	float SpawnRadius = 1200.f;

	UPROPERTY(EditAnywhere,Category = "Spawner")
	bool bScaleOverTime = true;

	UPROPERTY(EditAnywhere,Category = "Spawner")
	TArray<int32> TypeWeights;

	

protected:
	virtual void BeginPlay() override;

private :

	FTimerHandle SpawnTimerHandle;

	TArray<TWeakObjectPtr<AEnemyCharacter>> AllEnemiesAlive;

	int32 GetAliveCount();

	FVector PickSpawnPointAroundPlayer() const;

	TSubclassOf<AEnemyCharacter> PickEnemyClass() const;
	
	void SpawnTick();

	
};
