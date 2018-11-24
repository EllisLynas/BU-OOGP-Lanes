#include "EndGameScreen.h"

EndGameScreen::EndGameScreen()
{
}

EndGameScreen::~EndGameScreen()
{
}

EndGameScreen::State EndGameScreen::DisplayEndGameScreen(sf::RenderWindow& window, int _score, int _roundLength)
{
	// BACKGROUND IMAGE
	sf::Texture t_InfoMenu;
	sf::Sprite s_InfoMenu;
	t_InfoMenu.loadFromFile("Resources/EndMenu.png");
	s_InfoMenu.setTexture(t_InfoMenu);

	//RESULT
	sf::Font font;
	if (!font.loadFromFile("Resources/Font/Montserrat-Bold.ttf"))
	{
		std::cout << "ERROR LOADING FONT" << std::endl;
	}

	sf::Text t_FinalScore;
	t_FinalScore.setFillColor(sf::Color(0, 0, 0));
	t_FinalScore.setString(std::to_string(_score) + " / " + std::to_string(_roundLength));
	t_FinalScore.setCharacterSize(82);
	t_FinalScore.setFont(font);
	sf::FloatRect FinalScoreRect = t_FinalScore.getLocalBounds();
	t_FinalScore.setOrigin(FinalScoreRect.width / 2, FinalScoreRect.height / 2);
	t_FinalScore.setPosition(240, 460);

	// PLAY BUTTON
	sf::Texture t_btn_Play;
	sf::Sprite s_btn_Play;
	t_btn_Play.loadFromFile("Resources/btn_Replay.png");
	sf::Vector2u play_buttonSize = t_btn_Play.getSize();
	s_btn_Play.setTexture(t_btn_Play);
	s_btn_Play.setOrigin(play_buttonSize.x / 2, play_buttonSize.y / 2);
	s_btn_Play.setPosition(240, 688);

	// MENU BUTTON
	sf::Texture t_btn_Exit;
	sf::Sprite s_btn_Exit;
	t_btn_Exit.loadFromFile("Resources/btn_MainMenu.png");
	sf::Vector2u exit_buttonSize = t_btn_Exit.getSize();
	s_btn_Exit.setTexture(t_btn_Exit);
	s_btn_Exit.setOrigin(exit_buttonSize.x / 2, exit_buttonSize.y / 2);
	s_btn_Exit.setPosition(240, 748);

	window.draw(s_InfoMenu);
	window.draw(t_FinalScore);
	window.draw(s_btn_Play);
	window.draw(s_btn_Exit);
	window.display();

	Sleep(25);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::FloatRect btn_Play_Bounds = s_btn_Play.getGlobalBounds();
		sf::FloatRect btn_Exit_Bounds = s_btn_Exit.getGlobalBounds();

		if (btn_Play_Bounds.contains(mouse))
		{
			//std::cout << "REPLAY CLICKED" << std::endl;  // FOR DEBUG
			return Replay;
		}
		else if (btn_Exit_Bounds.contains(mouse))
		{
			//std::cout << "EXIT CLICKED" << std::endl;  // FOR DEBUG
			return MainMenu;
		}
	}
}