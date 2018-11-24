#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>
#include <Windows.h>

class EndGameScreen
{
public:
	enum State { Nothing, Replay, MainMenu };

	struct MenuButton
	{
		sf::Vector2i m_Position;
		sf::Image m_Image;
		State m_Action;
	};

	State DisplayEndGameScreen(sf::RenderWindow& window, int _score, int _roundLength);

	EndGameScreen();
	~EndGameScreen();
};