#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

#include <iostream>

#include "GameObject.h"
#include "MainScreen.h"
#include "ControlsScreen.h"
#include "ObjectiveScreen.h"
#include "EndGameScreen.h"
#include "Player.h"
#include "Line.h"

class Engine
{
private:
	static sf::Music m_Music;
	static sf::SoundBuffer m_Buffer;
	static sf::Sound m_Sound;

public:
	enum GameState
	{
		NotSet, MainMenuScreen, ControlsMenuScreen, ObjectiveMenuScreen,
		PlayGame, Replay, EndScreen, ExitGame
	};
	static GameState m_GameState;
	static void CreateGameWindow(sf::RenderWindow &_window, sf::Vector2f _windowSize, std::string _title, int _frames);
	static GameState GetState() { return m_GameState; }
	static void SetState(GameState _state) { m_GameState = _state; }

	static void DisplayMainMenuScreen(sf::RenderWindow &_window);
	static void DisplayControlsScreen(sf::RenderWindow &_window);
	static void DisplayObjectiveScreen(sf::RenderWindow &_window);
	static void DisplayEndScreen(sf::RenderWindow &_window, int _score, int _roundLength);

	// BACKGROUND MUSIC
	static void m_PlayBGMusic()
	{
		if (!m_Music.openFromFile("Resources/Sounds/BackgroundMusic.wav"))
		{
			std::cout << "BACKGROUND MUSIC AUDIO ERROR" << std::endl;
		}
		else
		{
			m_Music.setLoop(true);
			m_Music.setVolume(10);
			m_Music.play();
		}
	}

	// MOVE SOUND EFFECT
	static void m_PlayerMoveSound()
	{
		if (!m_Buffer.loadFromFile("Resources/Sounds/WooshSE2.wav"))
		{
			std::cout << "WOOSH SOUND AUDIO ERROR" << std::endl;
		}
		m_Sound.setVolume(15);
		m_Sound.setBuffer(m_Buffer);
		m_Sound.play();
	}

	// SCORE SOUND EFFECT
	static void m_ScoreSound()
	{
		if (!m_Buffer.loadFromFile("Resources/Sounds/PingSE.wav"))
		{
			std::cout << "SCORE SOUND AUDIO ERROR" << std::endl;
		}
		m_Sound.setVolume(12);
		m_Sound.setBuffer(m_Buffer);
		m_Sound.play();
	}

	Engine();
	~Engine();
};