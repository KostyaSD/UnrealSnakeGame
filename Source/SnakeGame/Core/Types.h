// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/List.h"

namespace SnakeGame
{

struct Dim
{
	uint32 width;
	uint32 height;
};

struct SNAKEGAME_API Position
{
	Position(uint32 inX, uint32 inY) : x(inX), y(inY) {}
	// Position() = default;

	uint32 x{0};
	uint32 y{0};

	FORCEINLINE Position& operator+=(const Position& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	// FORCEINLINE bool operator==(const Position& rhs) const { return x == rhs.x && y == rhs.y; }
	// FORCEINLINE bool IsEqual(const Position& rhs) const { return x == rhs.x && y == rhs.y; }

	static const Position Zero;
};

struct SNAKEGAME_API Input
{
	int8 x; /* possible values: (-1, 0, 1) */
	int8 y; /* possible values: (-1, 0, 1) */

	FORCEINLINE bool opposite(const Input& rhs) const  //
	{
		return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
	}

	static const Input Default;
};

enum class CellType
{
	Empty = 0,
	Wall,
	Snake,
	Food
};

struct Settings
{
	Dim gridDims{40, 10};
	struct Snake
	{
		uint32 defaultSize{4};
		Position startPosition{Position::Zero};
	} snake;
	float gameSpeed{1.0f};
};

using TPositionPtr = TDoubleLinkedList<Position>::TDoubleLinkedListNode;
class TSnakeList : public TDoubleLinkedList<Position>
{
public:
	void MoveTail(TPositionPtr* Tail, TPositionPtr* Head, const Position& Pos)
	{
		RemoveNode(Tail);
		InsertNode(Pos, Head->GetNextNode());
	}
};

}  // namespace SnakeGame