#pragma once

#include <SFML\Graphics.hpp>

#include "GameObject.h"

class Player :	public GameObject
{
public:
	enum m_Control { Left, Right };
	m_Control m_UserInput;
	enum PlayerColumn { None, C1, C2, C3, C4, C5 };
	PlayerColumn m_PlayerColumn;
	void SetColumn(int _column);
	virtual void Move(sf::Keyboard::Key _control);
	virtual void UpdatePosition();

	Player();
	~Player();
};