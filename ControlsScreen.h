#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>
#include <Windows.h>

class ControlsScreen
{
public:
	enum MenuState { Nothing, Play };
	MenuState DisplayControlsScreen(sf::RenderWindow& window);

	ControlsScreen();
	~ControlsScreen();
};