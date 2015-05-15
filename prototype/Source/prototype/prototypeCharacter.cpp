// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "prototype.h"
#include "prototypeCharacter.h"
#include "Engine.h"

AprototypeCharacter::AprototypeCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AprototypeCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("MouseButton_Left", IE_Pressed, this, &AprototypeCharacter::MoveCommand_MouseDown);
	InputComponent->BindAction("MouseButton_Left", IE_Released, this, &AprototypeCharacter::MoveCommand_MouseUp);
}

// Called every frame
void AprototypeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AprototypeCharacter::MoveCommand_MouseDown()
{
	static const bool bTraceComplex = false;
	FHitResult HitResult;

	static FVector2D Position = FVector2D::ZeroVector;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(Position.X, Position.Y);
	if (GetWorld()->GetFirstPlayerController()->GetHitResultAtScreenPosition(Position, ECC_Visibility, bTraceComplex, HitResult) == true)
	{
		CharacterIsSelected = false; //First assume the player character was not clicked...
		APawn* ClickedPawn = Cast<APawn>(HitResult.GetActor());
		if (ClickedPawn == Cast<APawn>(this))
		{
			//The player character was clicked!
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "FOO");
			CharacterIsSelected = true;
		}
	}
}

void AprototypeCharacter::MoveCommand_MouseUp()
{
	CharacterIsSelected = false;
}