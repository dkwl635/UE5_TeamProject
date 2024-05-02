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
USTRUCT(BlueprintType)
struct UPORTFOLIO_RPG_API FInventorySlotData : public FSlotData
{
	GENERATED_BODY()

public:
	FInventorySlotData();

	Inventory Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemIndex = -1;



	// USlotData을(를) 통해 상속됨
	bool IsValid() override;
	UTexture2D* GetSlotImg() override;
	bool NormalUse() override;

	
	//서로 상호작용이되는 슬롯들

};
