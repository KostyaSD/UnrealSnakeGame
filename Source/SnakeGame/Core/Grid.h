// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Utils.h"

namespace SnakeGame
{

class SNAKEGAME_API Grid
{
public:
	Grid(const Dim& dim, const IPositionRandomizerPtr& randomizer = MakeShared<PositionRandomizer>());

	static Position center(uint32 width, uint32 height) { return Position(width / 2 + 1, height / 2 + 1); }

	Dim dim() const { return c_dim; }

	void update(const TPositionPtr* links, CellType cellType);

	void update(const Position& position, CellType cellType);

	bool hitTest(const Position& position, CellType cellType) const;

	UE_NODISCARD bool randomEmptyPosition(Position& position) const;

	void printDebug();

private:
	const Dim c_dim;
	TArray<CellType> m_cells;
	TMap<CellType, TArray<uint32>> m_indByType = {
		{CellType::Snake, {}},	//
		{CellType::Wall, {}},	//
		{CellType::Food, {}},	//
	};

	TSharedPtr<IPositionRandomizer> m_positionRandomizer;

	void initWalls();
	void updateInternal(const Position& position, CellType cellType);
	void freeCellsByType(CellType cellType);

	FORCEINLINE uint32 posToIndex(uint32 x, uint32 y) const;
	FORCEINLINE uint32 posToIndex(const Position& position) const;
};
}  // namespace SnakeGame