#include "Game.h"

sf::Clock m_Clock;

Game::Game()
{
}

Game::~Game()
{
}

// GAME ENTRY POINT
void Game::Start(void)
{
	if (Engine::GetState() != Engine::NotSet)
	{
		return;
	}

	// CREATE WINDOW
	Engine::CreateGameWindow(m_Window, sf::Vector2f(480, 880), "LANES", 60);

	// SET STATE TO 'MAIN MENU'
	Engine::SetState(Engine::MainMenuScreen);
	Game::m_InGameState = Game::Normal;

	// PLAY BACKGROUND MUSIC
	Engine::m_PlayBGMusic();

	// ---------- GAME SETUP ----------

	// SETUP NEW GAME
	SetupNewGame();

	// SEED RANDOM NUMBER GENERATOR
	time_t qTime;
	time(&qTime);
	srand(qTime);
	srand(time(NULL));

	// ----------

	// WHITE THE GAME IS NOT EXITING, RUN THE GAME LOOP.
	while (!GameExiting())
	{
		GameLoop();
	}

	// CLOSE WINDOW
	m_Window.close();
}

// GAME LOOP (MANAGES GAME STATES, MENUS etc.)
void Game::GameLoop()
{
	switch (Engine::m_GameState)
	{
		case Engine::MainMenuScreen:
		{
			SetupNewGame();
			Engine::DisplayMainMenuScreen(m_Window);
			break;
		}
		case Engine::ControlsMenuScreen:
		{
			Engine::DisplayControlsScreen(m_Window);
			break;
		}
		case Engine::ObjectiveMenuScreen:
		{
			Engine::DisplayObjectiveScreen(m_Window);
			break;
		}
		case Engine::PlayGame:
		{
			// ---------- GAME LOOP ----------

			m_Window.clear(sf::Color(255, 255, 255));

			// ----- SET OBJECT POSITION

			// PLAYER
			m_Player.UpdatePosition();

			// ----- DRAW SPRITES -----
			m_Background.DrawObject(m_Window);
			m_LineOne.DrawObject(m_Window);
			m_LineOverlay.DrawObject(m_Window);
			m_Player.DrawObject(m_Window);
			m_UIOverlay.DrawObject(m_Window);
			// -----

			// ----- DISPLAY TEXT
			#pragma region DisplayTextToScreen

			// ROUND TITLE
			sf::Font f_roundTitle;
			if (!f_roundTitle.loadFromFile("Resources/Font/Montserrat-Bold.ttf"))
			{
				std::cout << "ERROR LOADING FONT" << std::endl;
			}

			sf::Text t_roundTitle;
			t_roundTitle.setString("Round " + std::to_string(Game::m_GameRound));
			t_roundTitle.setCharacterSize(28);
			t_roundTitle.setFont(f_roundTitle);
			sf::FloatRect textTitleRect = t_roundTitle.getLocalBounds();
			t_roundTitle.setOrigin(textTitleRect.width / 2, textTitleRect.height / 2);
			t_roundTitle.setPosition(240, 22);

			// PROGRESS
			sf::Font f_RegularFont;
			if (!f_RegularFont.loadFromFile("Resources/Font/Montserrat-Regular.ttf"))
			{
				std::cout << "ERROR LOADING FONT" << std::endl;
			}

			sf::Text t_progressText;
			t_progressText.setString(std::to_string(m_LineCount) + " / " + std::to_string(m_RoundLength));
			t_progressText.setCharacterSize(22);
			t_progressText.setFont(f_RegularFont);
			sf::FloatRect textProgRect = t_progressText.getLocalBounds();
			t_progressText.setOrigin(textProgRect.width, textProgRect.height / 2);
			t_progressText.setPosition(450, 27);

			// SCORE
			sf::Text t_scoreText;
			t_scoreText.setString(std::to_string(Game::m_Score));
			t_scoreText.setCharacterSize(22);
			t_scoreText.setFont(f_RegularFont);
			sf::FloatRect textScoreRect = t_scoreText.getLocalBounds();
			t_scoreText.setOrigin(0, textScoreRect.height / 2);
			t_scoreText.setPosition(32, 24);

			m_Window.draw(t_progressText);
			m_Window.draw(t_roundTitle);
			m_Window.draw(t_scoreText);
			#pragma endregion
			// -----

			// ----- LINES
			m_LineOne.Scroll(m_ScrollSpeed);
			m_LineOverlay.SetPosition(m_LineOne.GetStoredPosition().x, m_LineOne.GetStoredPosition().y);

			if (m_InGameState != End)
			{
				LinePositionCheck(m_LineOne, m_LineOverlay);
			}

			// ----- COLLISION DETECTION

			// SCORE AND LINE COLOUR CHANGE
			if (ColumnCollision(m_Player, m_LineOverlay) && m_LineOne.m_LineType != Line::Finish)
			{
				Engine::m_ScoreSound();
				Game::m_Score++;
				m_LineOne.LoadObject("Resources/GreyLine.png");
			}

			// SCROLL SPEED AND LINE COUNT
			if (LineCollision(m_Player, m_LineOne) && m_LineCount < Game::m_RoundLength)
			{
				IncreaseScrollSpeed();
				Game::m_LineCount++;
			}

			// CROSS FINISH LINE
			if (m_LineCount == m_RoundLength && CheckCollision(m_Player, m_LineOne) && m_LineOne.m_LineType == Line::Finish)
			{				
				Game::m_InGameState = Game::End;
				m_Clock.restart();
			}

			// END GAME APPROXIMATELY 1 SECONDS AFTER CROSSING THE FINISH LINE
			if (m_InGameState == Game::End)
			{
				sf::Time m_Time = m_Clock.getElapsedTime();

				if (m_Time.asSeconds() > 1.0f)
				{
					Engine::m_GameState = Engine::EndScreen;
				}
			}
			// -----

			// ----- DISPLAY ALL TO SCREEN -----
			m_Window.display();
			// -----

			EventLoop();
	
			break;
		}
		case Engine::EndScreen:
		{
			Engine::DisplayEndScreen(m_Window, m_Score, m_RoundLength);
			break;
		}
		case Engine::Replay:
		{
			SetupNewGame();
			Engine::m_GameState = Engine::PlayGame;
		}
	}
}

// GAME EVENT LOOP
void Game::EventLoop()
{
	// ---------- EVENT LOOP ----------
	sf::Event thisEvent;
	while (m_Window.pollEvent(thisEvent))
	{
		if (thisEvent.type == sf::Event::Closed)
		{
			Engine::m_GameState = Engine::ExitGame;
		}
		if (thisEvent.type == sf::Event::KeyReleased)
		{
			if (thisEvent.key.code == sf::Keyboard::Left)
			{
				//std::cout << "KEYBOARD IN USE (LEFT)" << std::endl; // FOR DEBUG
				Engine::m_PlayerMoveSound();
				m_Player.Move(sf::Keyboard::Left);
			}
			else if (thisEvent.key.code == sf::Keyboard::Right)
			{
				//std::cout << "KEYBOARD IN USE (RIGHT)" << std::endl;  // FOR DEBUG
				Engine::m_PlayerMoveSound();
				m_Player.Move(sf::Keyboard::Right);
			}
			else if (thisEvent.key.code == sf::Keyboard::Space)
			{
				// DEVELOPER USE: PRESS SPACEBAR FOR VALUES
				/*
				std::cout << "LINE TYPE: " << m_LineOne.m_LineType << std::endl;
				std::cout << "LINEOVERLAY POSITION: " << m_LineOverlay.m_OverlayPosition << std::endl;
				std::cout << "PLAYER COLUMN: " << m_Player.m_PlayerColumn << std::endl;
				std::cout << "SCORE: " << Game::m_Score << std::endl;
				std::cout << "LINE COUNT: " << m_LineCount << std::endl;
				system("PAUSE");
				*/
			}
		}
	}
}

// HANDLES GAME EXITING STATE
bool Game::GameExiting()
{
	if (Engine::GetState() == Engine::ExitGame)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// BASIC OBJECT-OBJECT COLLISION (BOUNDS)
bool Game::CheckCollision(GameObject _objectOne, GameObject _objectTwo)
{
	if (_objectOne.GetSprite().getGlobalBounds().intersects(_objectTwo.GetSprite().getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// PLAYER COLLISION WITH LINE (USED TO COUNT LINES PASSED)
bool Game::LineCollision(Player _player, Line& _line)
{
	if (CheckCollision(_player, _line) && _line.m_LineCounted == false)
	{
		_line.m_LineCounted = true;
		return true;
	}
	else
	{
		return false;
	}
}

// PLAYER COLLISION WITH LINE (USED TO DETECT COLLISION WITH LINE ONLY ONCE TO INCREMENT SCORE BY SINGLE VALUE)
bool Game::ColumnCollision(Player _player, Line& _line)
{
	if (_player.m_PlayerColumn == _line.m_OverlayPosition && CheckCollision(_player, _line) && _line.m_ScoreClaimed == false)
	{
		_line.m_ScoreClaimed = true;
		return true;
	}
	else
	{
		return false;
	}
}

// SETUP LINE AND LINEOVERLAY OBJECTS TO 1/5 RANDOM TYPES OR FINISH LINE 
void Game::SetupLineColour(Line& _line, Line& _overlay)
{
	if (m_LineCount == m_RoundLength && m_LineCount != 0)
	{
		_line.m_LineType = Line::Finish;
		_overlay.m_OverlayPosition = Line::C3;
		_line.LoadObject("Resources/FinishLine.png");
		_overlay.LoadObject("Resources/FinishOverlay.png");
	}
	else if (m_LineCount < m_RoundLength)
	{
		// ----- CHOOSE SIDE AT RANDOM
		int randomColour = rand() % 10;

		//  { Blue, Green, Pink, Purple, Yellow };

		if (randomColour == 0 || randomColour == 2)
		{
			_line.m_LineType = Line::Blue;
			_overlay.m_OverlayPosition = Line::C3;
			_line.LoadObject("Resources/BlueLine.png");
			_overlay.LoadObject("Resources/BlueLineOverlay.png");
		}
		else if (randomColour == 1 || randomColour == 3)
		{
			_line.m_LineType = Line::Green;
			_overlay.m_OverlayPosition = Line::C4;
			_line.LoadObject("Resources/GreenLine.png");
			_overlay.LoadObject("Resources/GreenLineOverlay.png");
		}
		else if (randomColour == 4 || randomColour == 6)
		{
			_line.m_LineType = Line::Pink;
			_overlay.m_OverlayPosition = Line::C1;
			_line.LoadObject("Resources/PinkLine.png");
			_overlay.LoadObject("Resources/PinkLineOverlay.png");
		}
		else if (randomColour == 5 || randomColour == 7)
		{
			_line.m_LineType = Line::Purple;
			_overlay.m_OverlayPosition = Line::C2;
			_line.LoadObject("Resources/PurpleLine.png");
			_overlay.LoadObject("Resources/PurpleLineOverlay.png");
		}
		else if (randomColour == 8 || randomColour == 9)
		{
			_line.m_LineType = Line::Yellow;
			_overlay.m_OverlayPosition = Line::C5;
			_line.LoadObject("Resources/YellowLine.png");
			_overlay.LoadObject("Resources/YellowLineOverlay.png");
		}
	}
}

// RESET THE LINE ATTRIBUTES AND POSITION TO TOP OF THE SCREEN
void Game::LinePositionCheck(Line& _line, Line& _overlay)
{
	if (_line.GetStoredPosition().y > 900)
	{
		_overlay.m_ScoreClaimed = false;
		_line.m_LineCounted = false;
		_line.SetObjectPosition(240, -30);
		SetupLineColour(_line, _overlay);
	}
}

// FOR SETTING UP A NEW GAME: LOAD OBJECTS AND RESET VARIABLES
void Game::SetupNewGame()
{
	// ----- LOAD OBJECTS
	m_Player.LoadObject("Resources/Player.png");
	m_LineOne.LoadObject("Resources/BlueLine.png");
	m_LineOverlay.LoadObject("Resources/BlueLineOverlay.png");
	m_Background.LoadObject("Resources/GameBackground.png");
	m_UIOverlay.LoadObject("Resources/GameOverlay.png");

	// ----- LINE SETUP
	m_LineOverlay.m_ScoreClaimed = false;
	m_LineOne.SetObjectPosition(240, -30);
	m_LineOverlay.SetObjectPosition(m_LineOne.GetStoredPosition().x, m_LineOne.GetStoredPosition().y);

	// ----- VARIABLES
	SetScrollSpeed(5);
	Game::m_GameRound = 1;
	Game::m_Score = 0;
	m_Player.SetColumn(3);
	Game::m_InGameState = Game::Normal;
	m_LineCount = 0;

	Game::m_LineOne.m_LineCounted = false;

	SetupLineColour(m_LineOne, m_LineOverlay);
}

// INCREMENTS SCROLL SPEED BY 1 IF SCORE IS WITHIN CERTAIN VALUES
void Game::IncreaseScrollSpeed()
{
	if (m_LineCount > 5 && m_LineCount < 9)
	{
		m_ScrollSpeed++;
	}
	else if (m_LineCount > 15 && m_LineCount < 20)
	{
		m_ScrollSpeed++;
	}
}

Engine::GameState Engine::m_GameState = NotSet;
Game::InGameState Game::m_InGameState = Game::Normal;
sf::RenderWindow Game::m_Window;
Player Game::m_Player;
GameObject Game::m_Background;
GameObject Game::m_UIOverlay;
int Game::m_Score;
int Game::m_GameRound;
Line Game::m_LineOne;
int Game::m_ScrollSpeed;
Line Game::m_LineOverlay;
int Game::m_LineCount = 0;
sf::Music Engine::m_Music;
sf::SoundBuffer Engine::m_Buffer;
sf::Sound Engine::m_Sound;