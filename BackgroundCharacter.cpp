// Fill out your copyright notice in the Description page of Project Settings.

#include "global.h"
#include "BackgroundCharacter.h"

// Sets default values
ABackgroundCharacter::ABackgroundCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent1"));

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetRelativeScale3D(FVector(10.f, 10.f, 0.1f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetupAttachment(RootComponent);

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("StaticMesh'/Engine/EditorMeshes/Cascade/BackgroundCube.BackgroundCube'"))
			, BaseMaterial(TEXT("MaterialInstanceConstant'/Game/NecrosUtilityMatPack/materials/wall/mi_concreteblocks_painted_yellow.mi_concreteblocks_painted_yellow'"))
			, BlueMaterial(TEXT("MaterialInstanceConstant'/Game/NecrosUtilityMatPack/materials/wall/mi_concreteblocks_painted_yellow.mi_concreteblocks_painted_yellow'"))
			, OrangeMaterial(TEXT("Material'/Game/NecrosUtilityMatPack/materials/floor/black.black'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();

	//BlockMesh->SetMaterial(0, BaseMaterial);
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());

}

// Called when the game starts or when spawned
void ABackgroundCharacter::BeginPlay()
{
	Super::BeginPlay();
	//BlockMesh->SetMaterial(0, BaseMaterial);
}

// Called every frame
void ABackgroundCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (g_status_code)
	{
	case 1:
		GetMesh()->SetVisibility(true);
		SetActorHiddenInGame(false);
		//BlockMesh->SetMaterial(0, BaseMaterial);
		g_status_code++;
		break;
	case 4:
		GetMesh()->SetVisibility(false);
		SetActorHiddenInGame(true);
		g_status_code++;
		break;
	}
}

// Called to bind functionality to input
void ABackgroundCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

