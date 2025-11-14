#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyAttackEnemyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LISAA_API UMyAttackEnemyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyAttackEnemyComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float Attackrange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float CoolDown = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float WindUpTime = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float HitRadius = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float YawTurnrate = 720.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float FacingTolerancedeg = 75.f;

	UFUNCTION(BlueprintCallable)
	void TryAttack(AActor* Target);

private:
	TWeakObjectPtr<class ACharacter> OwnerChar;
	bool bAttacking = false;
	float LastAttackTime = -1000.f;
	TWeakObjectPtr<AActor> Cachedtarget;

	FTimerHandle HitHandle;
	FTimerHandle EndHandle;

	void DotHit();
	void EndAttack();
	bool IsFacingTarget(AActor* Target) const;

	
};
