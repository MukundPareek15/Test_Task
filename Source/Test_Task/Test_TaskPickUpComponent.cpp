// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test_TaskPickUpComponent.h"

UTest_TaskPickUpComponent::UTest_TaskPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UTest_TaskPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UTest_TaskPickUpComponent::OnSphereBeginOverlap);
}

void UTest_TaskPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ATest_TaskCharacter* Character = Cast<ATest_TaskCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
