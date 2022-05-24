// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define QUARTER_VIEW_ANGLE	-45

#define MAX_PC_SKILL_COUNT	4
#define	MOVE_FORWARD		0x01
#define MOVE_RIGHT			0x02
#define MOVE_BACK			0x04
#define MOVE_LEFT			0x08


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)