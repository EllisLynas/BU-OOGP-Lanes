#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>

class MainScreen
{
public:
	enum MenuState { Nothing, Play, Exit };

	struct MenuButton
	{
		sf::Vector2i m_Position;
		sf::Image m_Image;
		MenuState m_Action;
	};

	MenuState DisplayMainScreen(sf::RenderWindow& window);

	MainScreen();
	~MainScreen();
};