// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, DeadActor);

// On health changed called when lost health, delta = lost helth number
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LISAA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION( BlueprintCallable )
	void ApplyDamage(float Amount, AActor* ActorInstigator = nullptr);

	UFUNCTION( BlueprintCallable )
	float GetHealth() const { return Health;}

	UFUNCTION( BlueprintCallable )
	float IsDead() const { return Health <= 0; }

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Health" )
	float MaxHealth = 50.f;

	UPROPERTY( BlueprintAssignable )
	FOnDeathSignature OnDeath;
	
	UPROPERTY( BlueprintAssignable )
	FOnHealthChanged OnHealthChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



private:
	float Health = 0.f;
		
};
