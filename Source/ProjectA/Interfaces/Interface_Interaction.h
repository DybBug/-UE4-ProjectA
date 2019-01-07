// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Interaction.generated.h"

class APlayer_Character;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Interaction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTA_API IInterface_Interaction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
private :
	APlayer_Character* m_pInteractionUser;

public:
	virtual void OnInteract(APlayer_Character* _pPlayer) = 0;
	virtual void UnInteract() = 0;

	/* Get */
	FORCEINLINE APlayer_Character* const& GetInteractionUser() const { return m_pInteractionUser; }
	
	/* Set */
	FORCEINLINE void SetInteractionUser(APlayer_Character* _pUser) { m_pInteractionUser = _pUser; }
};
