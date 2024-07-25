#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "../OSS.h"
#include "../UI/CMainMenuWidget.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClassAsset(TEXT("/Game/UI/WB_MainMenu"));
	if (MainMenuWidgetClassAsset.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetClassAsset.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuWidgetClassAsset(TEXT("/Game/UI/WB_InGameMenu"));
	if (InGameMenuWidgetClassAsset.Succeeded())
	{
		InGameMenuWidgetClass = InGameMenuWidgetClassAsset.Class;
	}
}

void UCGameInstance::Init()
{
	Super::Init();
}

void UCGameInstance::Host()
{
	LogOnScreen(this, "Host", FColor::Green);

	if (MainMenu)
	{
		MainMenu->SetInputToGame();
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	World->ServerTravel("/Game/Maps/Coop?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	LogOnScreen(this, "Join to " + InAddress, FColor::Green);

	if (MainMenu)
	{
		MainMenu->SetInputToGame();
	}

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		return;
	}

	PC->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::OpenMainMenuLevel()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		return;
	}

	PC->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::LoadMainMenu()
{
	ensure(MainMenuWidgetClass);

	MainMenu = CreateWidget<UCMainMenuWidget>(this, MainMenuWidgetClass);
	
	if (!MainMenu)
	{
		return;
	}

	MainMenu->SetOwningInstance(this);
	MainMenu->SetInputToUI();
}

void UCGameInstance::LoadInGameMenu()
{
	ensure(InGameMenuWidgetClass);

	UCMenuWidgetBase* InGameMenu = CreateWidget<UCMenuWidgetBase>(this, InGameMenuWidgetClass);
	if (!InGameMenu)
	{
		return;
	}

	InGameMenu->SetOwningInstance(this);
	InGameMenu->SetInputToUI();
}
