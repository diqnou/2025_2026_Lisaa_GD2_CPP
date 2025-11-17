#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UHealthComponent;

UCLASS()
class LISAA_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float TouchDamage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComp;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class UEnemyAttackComponent* AttackComp = nullptr;

	UFUNCTION()
	void OnSelfDeath(AActor* DeadActor);

};
