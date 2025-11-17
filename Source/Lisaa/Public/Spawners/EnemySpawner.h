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

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<TSubclassOf<AEnemyCharacter>> AllEnemyClasses;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnInterval = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 MaxAlive = 50;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnRadius = 1200.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	bool bScaleOverTime = true;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<int32> TypeWeights;	

protected:
	virtual void BeginPlay() override;

private:

	FTimerHandle SpawnTimer;

	void SpawnTick();

	TArray<TWeakObjectPtr<AEnemyCharacter>> AllEnemyAlive;

	int32 GetAliveCount();

	FVector PickSpawnPointAroundPlayer() const;

	TSubclassOf<AEnemyCharacter> PickEnemyClass() const;

};
