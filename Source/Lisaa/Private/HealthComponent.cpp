// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void UHealthComponent::ApplyDamage(float Amount, AActor* ActorInstigator)
{
	if (Amount <= 0 || IsDead())
 		return;

	const float OldHealth = Health;
	Health = FMath ::Clamp(Health - Amount, 0.f, MaxHealth);
	
	OnHealthChanged.Broadcast(Health, Health- OldHealth);

	if (Health <= 0.f)
		OnDeath.Broadcast( GetOwner());
	
}


