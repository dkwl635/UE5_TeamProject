// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "UI/RPGMainUserWidget.h"
#include "UI/RPGUserWidget.h"
#include "Item/ItemData.h"
#include "Components/CanvasPanelSlot.h"
#include "Skill/Skill_MainWidget.h"
#include "UI/RPGTextBox.h"


// Sets default values
AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<URPGMainUserWidget> FindUI(TEXT("Script/UMGEditor.WidgetBlueprint'/Game/KJW/UI/BPUI_MainUI.BPUI_MainUI_C'"));
 	MainUIBP = FindUI.Class;
}

void AUIManager::SpawnUI()
{
	if (MainUIBP)
	{
		auto Widget = CreateWidget<UUserWidget>(GetWorld(), MainUIBP);
		PlayerUI = Cast<URPGMainUserWidget>(Widget);
		PlayerUI->Init();
		PlayerUI->AddToViewport();
	}
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();


}


void AUIManager::ShowUI(ERPG_UI Type)
{
	URPGUserWidget* UserWidget = GetRPGUI(Type);
	if (!UserWidget) { return; }

	if (UIList.Num() > 0)
	{
		ERPG_UI TopUIType = UIList[0];
		if (TopUIType == ERPG_UI::TEXTBOX)
		{
			return;
		}

		GetCanvasPanel(TopUIType)->SetZOrder(PopupZOrder);
	}

	if (UIList.Contains(Type))
	{
		int index = UIList.IndexOfByKey(Type);
		UIList.RemoveAt(index);
	}
	UIList.Insert(Type, 0);

	UCanvasPanelSlot* Current = GetCanvasPanel(UserWidget->UI_Type);
	Current->SetZOrder(TopZOrder);

	if (Type == ERPG_UI::TEXTBOX)
	{
		Current->SetZOrder(TextZOrder);
	}

	if (UserWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		UserWidget->SetVisibility(ESlateVisibility::Visible);
		UserWidget->ShowInitUI();
		UserWidget->RefreshUI();
	}
}



void AUIManager::HideUI(ERPG_UI Type)
{
	URPGUserWidget* UserWidget = GetRPGUI(Type);
	if (!UserWidget) { return; }

	if (UIList.Contains(Type))
	{
		int index = UIList.IndexOfByKey(Type);
		UIList.RemoveAt(index);
	}

	if (UIList.Num() > 0)
	{
		ERPG_UI TopUIType = UIList[0];
		GetCanvasPanel(TopUIType)->SetZOrder(TopZOrder);
	}

	UserWidget->HideSetUI();
	UserWidget->SetVisibility(ESlateVisibility::Collapsed);

}

void AUIManager::TopHideUI()
{
	if (UIList.Num() > 0)
	{
		ERPG_UI TopUIType = UIList[0];
		HideUI(TopUIType);
	}
}

UCanvasPanelSlot* AUIManager::GetCanvasPanel(ERPG_UI Type)
{
	return PlayerUI->GetCanvasPanel(Type);
}

void AUIManager::PlayerGoodsUIRefresh()
{
	PlayerUI->PlayerGoodsRefresh();
}

void AUIManager::ShowItemBox(FVector2D SpawnPos, ShowBoxData Data)
{
	PlayerUI->ShowItemInfoBox(SpawnPos ,Data);
}

void AUIManager::HideItemBox()
{
	PlayerUI->HideItemInfoBox();
}

void AUIManager::RefreshUI(ERPG_UI UIType)
{
	PlayerUI->RPGUIRefresh(UIType);
}

void AUIManager::SetSkillUI()
{
	PlayerUI->SkillWidget->SetUIInfo();
}

void AUIManager::SetYesNoButton(FOnButtonCallBack YesButtonFunc, FOnButtonCallBack NoButtonFunc, FText BoxText)
{

	if (PlayerUI)
	{
		PlayerUI->TextBox->SetYesNoButton(YesButtonFunc, NoButtonFunc, BoxText);
	}
}


URPGUserWidget* AUIManager::GetRPGUI(ERPG_UI UIType)
{
	return PlayerUI->GetRPGUI(UIType);
}

bool AUIManager::IsShowUI(ERPG_UI UIType)
{
	if (UIList.Contains(UIType))
	{
		return true;
	}

	return false;
}

void AUIManager::GetRPGUIToggle(ERPG_UI UIType)
{
	if (IsShowUI(UIType))
	{
		HideUI(UIType);
	}
	else
	{
		ShowUI(UIType);
	}
}


