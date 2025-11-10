#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LISAA_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()



public:	
	UMyActorComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

	UPROPERTY(EditAnywhere, Category = "AI")
	float StopDistance = 75.f;

protected:
	
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<class ACharacter> OwnerChar;

};
