// Fill out your copyright notice in the Description page of Project Settings.


#include "TextPawn.h"
#include "global.h"
#include <ctime>
#include "Components/TextRenderComponent.h"
// Sets default values
ATextPawn::ATextPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	srand((int)time(0));
}

// Called when the game starts or when spawned
void ATextPawn::BeginPlay()
{
	Super::BeginPlay();

	Text = GetWorld()->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), FVector(20.f, 20.f, 0.1f), FRotator(90.f, 180.f, 0.f));
	Text->GetTextRender()->SetText(FText::FromString(TEXT("Dynamic Text")));
	Text->GetTextRender()->SetTextRenderColor(FColor::Red);
	Text->SetActorScale3D(FVector(5.f, 5.f, 5.f));
}

void ATextPawn::GenerateText(bool isMask)
{
	if (isMask)
	{
		Text->GetTextRender()->SetTextRenderColor(FColor(0, 255, 0, 255));
	}
	else
	{
		int textLength = rand() % 9;
		std::string text = "";
		for (int i = 0; i < textLength; i++)
		{
			char c;
			if (rand() % 2)
			{
				c = rand() % 26 + 97;
			}
			else
			{
				c = rand() % 26 + 65;
			}
			text += c;
		}
		Text->GetTextRender()->SetText(FText::FromString(text.c_str()));
		int color[4];
		for (int i = 0; i < 4; i++)
		{
			color[i] = rand() % 256;
		}
		Text->GetTextRender()->SetTextRenderColor(FColor(color[0], color[1], color[2], color[3]));
	}
}

// Called every frame
void ATextPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (g_status_code)
	{
	case 0:
		GenerateText(false);
		g_status_code++;
		break;
	case 3:
		GenerateText(true);
		g_status_code++;
		break;
	}
}

// Called to bind functionality to input
void ATextPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

