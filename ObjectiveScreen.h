#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>
#include <Windows.h>

class ObjectiveScreen
{
public:
	enum MenuState { Nothing, Play, Exit };

	struct MenuButton
	{
		sf::Vector2i m_Position;
		sf::Image m_Image;
		MenuState m_Action;
	};

	MenuState DisplayObjectiveScreen(sf::RenderWindow& window);
	ObjectiveScreen();
	~ObjectiveScreen();
};