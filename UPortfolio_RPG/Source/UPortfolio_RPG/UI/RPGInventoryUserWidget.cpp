// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGInventoryUserWidget.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Slot/SlotData.h"
#include "Slot/InventorySlotData.h"
#include	"Item/ItemEnum.h"

void URPGInventoryUserWidget::Init()
{
	//return;
	int32 Col = InvenSlotSizeX;
	int32 Row = InvenSlotSizeY;

	UPlayerInventorySubsystem* Inven = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	if (!Inven)
	{
		return;
	}	

	for (int32 i = 0; i < Row; i++)
	{
		for (int32 k = 0; k < Col; k++)
		{
			URPGSlotUserWidget* SlotrWidget = Cast<URPGSlotUserWidget>(CreateWidget(this, SlotBP));
			ensure(SlotrWidget);
			SlotrWidget->SlotType = ERPGSLOTTYPE::INVENTORY_GEAR;
			SlotrWidget->Init();
			GearBox->AddChildToUniformGrid(SlotrWidget, i, k);
			auto slotData = SlotrWidget->GetSlotData();
			if (!slotData)
			{
				UE_LOG(LogTemp, Display, TEXT("slotData null"));
			}
			else
			{
				UInventorySlotData* InvenSlotData = (UInventorySlotData*)slotData;
				InvenSlotData->SlotIndex = k + i * Col;
			
				GearSlots.Add(SlotrWidget);
				SlotrWidget->RefreshSlot();
			}
		}		
	}

	for (int32 i = 0; i < Row; i++)
	{
		for (int32 k = 0; k < Col; k++)
		{
			URPGSlotUserWidget* SlotWidget = Cast<URPGSlotUserWidget>(CreateWidget(this, SlotBP));
			ensure(SlotWidget);
			SlotWidget->SlotType = ERPGSLOTTYPE::INVENTORY_NORMARL;
			SlotWidget->Init();
			NormalBox->AddChildToUniformGrid(SlotWidget, i, k);
			auto slotData = SlotWidget->GetSlotData();
			if (!slotData)
			{
				UE_LOG(LogTemp, Display, TEXT("slotData null"));
			}
			else
			{
				UInventorySlotData* InvenSlotData = (UInventorySlotData*)slotData;
				InvenSlotData->SlotIndex = k + i * Col;
	
				NormalSlots.Add(SlotWidget);
				SlotWidget->RefreshSlot();
			}	
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("My Name: %d ,: %d"), NormalSlots.Num(), GearSlots.Num());
	

	
}

void URPGInventoryUserWidget::RefreshUI()
{
	int bagIndex = BagWidgetSwitcher->GetActiveWidgetIndex();
	if (bagIndex == 0)
	{
		GearInventoryRefresh();
	}
	else if (bagIndex == 1)
	{
		NormalInventoryRefresh();
	}
}

void URPGInventoryUserWidget::GearInventoryRefresh()
{
	int32 Size = GearSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		GearSlots[i]->RefreshUI();
	}
}

void URPGInventoryUserWidget::NormalInventoryRefresh()
{
	int32 Size = NormalSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		NormalSlots[i]->RefreshUI();
	}
}
