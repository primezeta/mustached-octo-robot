// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "prototype.h"
#include "prototypeCharacter.h"

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
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//InputComponent->BindAxis("MoveRight", this, &AprototypeCharacter::MoveRight);
	//InputComponent->BindTouch(IE_Pressed, this, &AprototypeCharacter::TouchStarted);
	//InputComponent->BindTouch(IE_Released, this, &AprototypeCharacter::TouchStopped);
	InputComponent->BindAction("MouseButton_Left", IE_Pressed, this, &AprototypeCharacter::MoveCommand_MouseDown);
	InputComponent->BindAction("MouseButton_Left", IE_Released, this, &AprototypeCharacter::MoveCommand_MouseUp);
}

// Called every frame
void AprototypeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CharacterIsSelected)
	{
		//ActorInteractor()->DrawMoveCommandLine(PlayerPosition(), MousePosition());
	}
}

//MouseDragLine.DrawLine(PlayerLocation, FVector(PlayerLocation.X, mx, my), LineColor, LineDepthPriority, LineThickness, LineLifeTime);
void AprototypeCharacter::MoveCommand_MouseDown()
{
	static const bool bTraceComplex = false;
	FHitResult HitResult;
	if (PlayerController()->GetHitResultAtScreenPosition(ScreenMousePosition(), ECC_Visibility, bTraceComplex, HitResult) == true)
	{
		CharacterIsSelected = false; //First assume the player character was not clicked...
		APawn* ClickedPawn = Cast<APawn>(HitResult.GetActor());
		if (ClickedPawn == Cast<APawn>(this))
		{
			//The player character was clicked!
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Yay!");
			CharacterIsSelected = true;
		}
	}
}

void AprototypeCharacter::MoveCommand_MouseUp()
{
	CharacterIsSelected = false;
}

//void AprototypeCharacter::MoveRight(float Value)
//{
//	// add movement in that direction
//	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
//}
//
//void AprototypeCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	// jump on any touch
//	Jump();
//}
//
//void AprototypeCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	StopJumping();
//}

APlayerController const * AprototypeCharacter::PlayerController()
{
	static APlayerController * ThePlayerController = nullptr;
	if (ThePlayerController == nullptr)
	{
		ThePlayerController = Cast<APlayerController>(GetController());
	}
	return ThePlayerController;
}

FVector AprototypeCharacter::MousePosition()
{
	static FVector Position;
	PlayerController()->GetMousePosition(Position.Y, Position.Z);
	Position.X = PlayerPosition().X;
	return Position;
}

FVector2D AprototypeCharacter::ScreenMousePosition()
{
	static FVector2D Position;
	PlayerController()->GetMousePosition(Position.X, Position.Y);
	return Position;
}

FVector AprototypeCharacter::PlayerPosition()
{
	static FVector Position;
	Position = this->GetActorLocation();
	return Position;
}