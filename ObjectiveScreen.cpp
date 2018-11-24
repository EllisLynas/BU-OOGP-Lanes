#include "ObjectiveScreen.h"

ObjectiveScreen::ObjectiveScreen()
{
}

ObjectiveScreen::~ObjectiveScreen()
{
}

ObjectiveScreen::MenuState ObjectiveScreen::DisplayObjectiveScreen(sf::RenderWindow& window)
{
	// BACKGROUND IMAGE
	sf::Texture t_Background;
	sf::Sprite s_Background;
	t_Background.loadFromFile("Resources/ObjectiveMenu.png");
	s_Background.setTexture(t_Background);

	// NEXT BUTTON
	sf::Texture t_btn_Next;
	sf::Sprite s_btn_Next;
	t_btn_Next.loadFromFile("Resources/btn_Play.png");
	sf::Vector2u next_buttonSize = t_btn_Next.getSize();
	s_btn_Next.setTexture(t_btn_Next);
	s_btn_Next.setOrigin(next_buttonSize.x / 2, next_buttonSize.y / 2);
	s_btn_Next.setPosition(240, 688);

	window.draw(s_Background);
	window.draw(s_btn_Next);
	window.display();

	Sleep(50);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::FloatRect btn_Next_Bounds = s_btn_Next.getGlobalBounds();

		if (btn_Next_Bounds.contains(mouse))
		{
			//std::cout << "PLAY CLICKED" << std::endl;  // FOR DEBUG
			return Play;
		}
	}
}