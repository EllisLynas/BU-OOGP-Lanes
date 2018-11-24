#pragma once

#include <ctime>
#include <vector>
#include <iostream>

#include "Engine.h"

class Game
{
public:
	enum InGameState { Normal, End };
	static InGameState m_InGameState;

	static void Start();

	static void SetScrollSpeed(int _speed) { m_ScrollSpeed = _speed; }
	virtual int GetScrollSpeed() { return m_ScrollSpeed; }

	static bool CheckCollision(GameObject _objectOne, GameObject _objectTwo);
	static bool LineCollision(Player _player, Line & _line);
	static bool ColumnCollision(Player _player, Line& _line);

private:
	static const int m_RoundLength = 20; // SET ROUND LENGTH
	static bool GameExiting();
	static void GameLoop();
	static void EventLoop();
	static void LinePositionCheck(Line& _line, Line& _overlay);
	static void SetupNewGame();
	static void IncreaseScrollSpeed();
	static sf::RenderWindow m_Window;
	static Player m_Player;
	static GameObject m_Background;
	static GameObject m_UIOverlay;
	static Line m_LineOne;
	static Line m_LineOverlay;
	static void SetupLineColour(Line& _line, Line& _overlay);
	static int m_Score;
	static int m_GameRound;
	static int m_ScrollSpeed;
	static int m_LineCount;

	Game();
	~Game();
};