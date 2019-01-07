// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager_Master.h"
#include "Manager_Item.h"


UManager_Master::UManager_Master()
{
	m_pItemManager = CreateDefaultSubobject<UManager_Item>("ItemManager");
}


