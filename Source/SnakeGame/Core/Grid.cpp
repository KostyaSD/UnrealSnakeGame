// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "Core/Grid.h"

DEFINE_LOG_CATEGORY_STATIC(LogGrid, All, All);

using namespace SnakeGame;

Grid::Grid(const Dim& dim)	//
	: c_dim(Dim{dim.width + 2, dim.height + 2})
{
	m_cells.Init(CellType::Empaty, c_dim.width * c_dim.height);
	initWalls();
	printDebug();
}

void Grid::initWalls()
{
	for (uint32 y = 0; y < c_dim.height; ++y)
	{
		for (uint32 x = 0; x < c_dim.width; ++x)
		{
			if (x == 0 || x == c_dim.width - 1 || y == 0 || y == c_dim.height - 1)
			{
				m_cells[posToIndex(x, y)] = CellType::Wall;
			}
		}
	}
}

void Grid::printDebug()
{
#if !UE_BUILD_SHIPPING
	for (uint32 y = 0; y < c_dim.height; ++y)
	{
		FString line;
		for (uint32 x = 0; x < c_dim.width; ++x)
		{
			TCHAR symbol{};
			switch (m_cells[posToIndex(x, y)])
			{
				case CellType::Empaty: symbol = '0'; break;
				case CellType::Wall: symbol = '*'; break;
				case CellType::Snake: symbol = '_'; break;
			}
			line.AppendChar(symbol).AppendChar(' ');
		}
		UE_LOG(LogGrid, Display, TEXT("%s"), *line);
	}
#endif
}

void Grid::update(const TPositionPtr* links, CellType cellType)
{
	freeCellsByType(cellType);
	auto* link = links;
	while (link)
	{
		const auto index = posToIndex(link->GetValue());
		m_cells[index] = cellType;
		link = link->GetNextNode();
		// updateInternal(link->GetValue(), cellType);
		// link = link->GetNextNode();
	}
}

void Grid::freeCellsByType(CellType cellType)
{
	for (auto& cell : m_cells)
	{
		if (cell == cellType)
		{
			cell = CellType::Empaty;
		}
	}
	// for (int32 i = 0; i < m_indByType[cellType].Num(); ++i)
	//{
	//	const uint32 ind = m_indByType[cellType][i];
	//	m_cells[ind] = CellType::Empty;
	// }
	// m_indByType[cellType].Empty();
}

bool Grid::hitTest(const Position& position, CellType cellType) const
{
	return m_cells[posToIndex(position)] == cellType;
}

uint32 Grid::posToIndex(uint32 x, uint32 y) const
{
	return x + y * c_dim.width;
}

uint32 Grid::posToIndex(const Position& position) const
{
	return posToIndex(position.x, position.y);
}
