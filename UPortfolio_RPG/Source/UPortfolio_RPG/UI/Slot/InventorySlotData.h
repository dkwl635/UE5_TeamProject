// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SlotData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Item/ItemData.h"
#include "InventorySlotData.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UInventorySlotData : public USlotData
{
	GENERATED_BODY()

public:
	UInventorySlotData();

	// USlotData을(를) 통해 상속됨
	bool IsValid() override;
	UTexture2D* GetSlotImg() override;
	bool NormalUse() override;


	Inventory Inventory;


	int ItemIndex = -1;

	//서로 상호작용이되는 
	int8 QuickSlotIndex = -1;
};
