// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "Core/Snake.h"

using namespace SnakeGame;

Snake::Snake(const Settings::Snake& settings)
{
	checkf(settings.defaultSize >= 4, TEXT("Snake lenght is too small: %i"), settings.defaultSize);

	// add snake links horizontaly to the left [ ----*]
	const auto startPos = settings.startPosition;
	for (uint32 i = 0; i < settings.defaultSize; ++i)
	{
		m_links.AddTail(Position{startPos.x - i, startPos.y});
	}
}

void Snake::move(const Input& input)
{

	m_links.RemoveNode(m_links.GetTail());
	m_links.InsertNode(m_links.GetHead()->GetValue(), m_links.GetHead()->GetNextNode());
	m_links.GetHead()->GetValue() += Position(input.x, input.y);
	// can't move opposite direction
	//if (!m_lastInput.opposite(input))
	//{
	//	m_lastInput = input;
	//}

	//m_links.GetTail()->GetValue() = m_links.GetHead()->GetValue();
	//m_links.MoveTailAfterHead();
	//m_links.GetHead()->GetValue() += Position(m_lastInput.x, m_lastInput.y);
}
