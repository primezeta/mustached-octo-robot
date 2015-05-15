// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Scene_LevelExtender.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROTOTYPE_API UScene_LevelExtender : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScene_LevelExtender();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Called when something overlaps with us
	UFUNCTION(Category="SceneLevelExtender")
	void OverlapStart(AActor * OtherActor);
};
