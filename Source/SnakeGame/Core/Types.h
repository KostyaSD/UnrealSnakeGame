// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace Snake
{

struct Dim
{
	int32 widht;
	int32 height;
};

enum class CellType
{
	Empaty = 0,
	Wall
	//Food
	//Snake
};

struct Settings
{
	Dim gridSize;
};

}  // namespace Snake