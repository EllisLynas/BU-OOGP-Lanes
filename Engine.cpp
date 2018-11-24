#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::CreateGameWindow(sf::RenderWindow &_window, sf::Vector2f _windowSize, std::string _title, int _frames)
{
	_window.create(sf::VideoMode(480, 880), _title, sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(_frames);
}

void Engine::DisplayMainMenuScreen(sf::RenderWindow &_window)
{
	// CREATE MAIN MENU OBJECT
	MainScreen screen;
	// CREATE MENU STATE OBJECT WHICH DISPLAYS THE MAIN MENU TO GET BUTTON CLICK
	MainScreen::MenuState menuState = screen.DisplayMainScreen(_window);
	// SET GAME STATE DEPENDING ON MENU STATE RETURNED ^
	switch (menuState)
	{
	case MainScreen::Play:
	{
		m_GameState = GameState::ControlsMenuScreen;
		break;
	}
	case MainScreen::Exit:
	{
		m_GameState = GameState::ExitGame;
		break;
	}
	}
}

void Engine::DisplayControlsScreen(sf::RenderWindow &_window)
{
	ControlsScreen screen;
	ControlsScreen::MenuState menuState = screen.DisplayControlsScreen(_window);
	switch (menuState)
	{
	case ControlsScreen::Play:
	{
		m_GameState = GameState::ObjectiveMenuScreen;
		break;
	}
	}
}

void Engine::DisplayObjectiveScreen(sf::RenderWindow &_window)
{
	ObjectiveScreen screen;
	ObjectiveScreen::MenuState menuState = screen.DisplayObjectiveScreen(_window);
	switch (menuState)
	{
	case ObjectiveScreen::Play:
	{
		m_GameState = GameState::PlayGame;
		break;
	}
	}
}

void Engine::DisplayEndScreen(sf::RenderWindow &_window, int _score, int _roundLength)
{
	EndGameScreen endMenu;
	EndGameScreen::State endMenuState = endMenu.DisplayEndGameScreen(_window, _score, _roundLength);
	switch (endMenuState)
	{
	case EndGameScreen::Replay:
	{
		m_GameState = GameState::Replay;
		break;
	}
	case EndGameScreen::MainMenu:
	{
		m_GameState = GameState::MainMenuScreen;
		break;
	}
	}
}