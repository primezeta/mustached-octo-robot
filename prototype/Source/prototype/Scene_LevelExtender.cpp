// Fill out your copyright notice in the Description page of Project Settings.

#include "prototype.h"
#include "GameFramework/Actor.h"
#include "Scene_LevelExtender.h"


// Sets default values for this component's properties
UScene_LevelExtender::UScene_LevelExtender()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScene_LevelExtender::InitializeComponent()
{
	Super::InitializeComponent();

	AActor * Parent = this->GetAttachmentRootActor();
	Parent->OnActorBeginOverlap.AddDynamic(this, &UScene_LevelExtender::OverlapStart);
}


// Called every frame
void UScene_LevelExtender::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UScene_LevelExtender::OverlapStart(AActor * OtherActor)
{
	if (OtherActor != Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		return;
	}

}