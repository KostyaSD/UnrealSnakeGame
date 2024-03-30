// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace SnakeGame
{

struct Dim
{
	uint32 width;
	uint32 height;
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
	Dim gridDims;
};

}  // namespace Snake