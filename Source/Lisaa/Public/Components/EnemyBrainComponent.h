#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyBrainComponent.generated.h"

class UMyAttackEnemyComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LISAA_API UEnemyBrainComponent : public UActorComponent

{
	GENERATED_BODY()

public:	
	UEnemyBrainComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, Category = "AI")
	float StopDistance = 75.f;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UMyAttackEnemyComponent* AttackComp = nullptr;
	
private:
	TWeakObjectPtr<class ACharacter> OwnerChar;



		
};
