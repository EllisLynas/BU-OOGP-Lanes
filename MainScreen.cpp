#include "MainScreen.h"

MainScreen::MainScreen()
{
}

MainScreen::~MainScreen()
{
}

MainScreen::MenuState MainScreen::DisplayMainScreen(sf::RenderWindow& window)
{
	// BACKGROUND IMAGE
	sf::Texture t_MainMenu;
	sf::Sprite s_MainMenu;
	t_MainMenu.loadFromFile("Resources/MainMenu.png");
	s_MainMenu.setTexture(t_MainMenu);

	// PLAY BUTTON
	sf::Texture t_btn_Play;
	sf::Sprite s_btn_Play;
	t_btn_Play.loadFromFile("Resources/btn_Play.png");
	sf::Vector2u play_buttonSize = t_btn_Play.getSize();
	s_btn_Play.setTexture(t_btn_Play);
	s_btn_Play.setOrigin(play_buttonSize.x / 2, play_buttonSize.y / 2);
	s_btn_Play.setPosition(240, 440);

	// EXIT BUTTON
	sf::Texture t_btn_Exit;
	sf::Sprite s_btn_Exit;
	t_btn_Exit.loadFromFile("Resources/btn_Exit.png");
	sf::Vector2u exit_buttonSize = t_btn_Exit.getSize();
	s_btn_Exit.setTexture(t_btn_Exit);
	s_btn_Exit.setOrigin(exit_buttonSize.x / 2, exit_buttonSize.y / 2);
	s_btn_Exit.setPosition(240, 500);

	window.draw(s_MainMenu);
	window.draw(s_btn_Play);
	window.draw(s_btn_Exit);
	window.display();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::FloatRect btn_Play_Bounds = s_btn_Play.getGlobalBounds();
		sf::FloatRect btn_Exit_Bounds = s_btn_Exit.getGlobalBounds();

		if (btn_Play_Bounds.contains(mouse))
		{
			//std::cout << "PLAY CLICKED" << std::endl;  // FOR DEBUG
			return Play;
		}
		else if (btn_Exit_Bounds.contains(mouse))
		{
			//std::cout << "EXIT CLICKED" << std::endl;  // FOR DEBUG
			return Exit;
		}
	}
}