#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Move(sf::Keyboard::Key _control)
{
	if (_control == sf::Keyboard::Key::Left)
	{
		switch (m_PlayerColumn)
		{
			case Player::C1:
			{
				m_PlayerColumn = C1;
				break;
			}
			case Player::C2:
			{
				m_PlayerColumn = C1;
				break;
			}
			case Player::C3:
			{
				m_PlayerColumn = C2;
				break;
			}
			case Player::C4:
			{
				m_PlayerColumn = C3;
				break;
			}
			case Player::C5:
			{
				m_PlayerColumn = C4;
				break;
			}
			default:
			{
				std::cout << "UNHANDLED COLUMN" << std::endl;
				break;
			}
		}
	}

	if (_control == sf::Keyboard::Key::Right)
	{
		switch (m_PlayerColumn)
		{
		case Player::C1:
		{
			m_PlayerColumn = C2;
		}
		break;
		case Player::C2:
		{
			m_PlayerColumn = C3;
		}
		break;
		case Player::C3:
		{
			m_PlayerColumn = C4;
		}
		break;
		case Player::C4:
		{
			m_PlayerColumn = C5;
		}
		break;
		case Player::C5:
		{
			m_PlayerColumn = C5;
		}
		break;
		default:
		{
			std::cout << "UNHANDLED COLUMN" << std::endl;
		}
		break;
		}

	}

	UpdatePosition();
}

void Player::UpdatePosition()
{
	switch (m_PlayerColumn)
	{
		case Player::C1:
		{
			SetPosition(72, 700);
			break;
		}
		case Player::C2:
		{
			SetPosition(156, 700);
			break;
		}
		case Player::C3:
		{
			SetPosition(240, 700);
			break;
		}
		case Player::C4:
		{
			SetPosition(324, 700);
			break;
		}
		case Player::C5:
		{
			SetPosition(408, 700);
			break;
		}
		default:
		{
			std::cout << "UNHANDLED COLUMN" << std::endl;
			break;
		}
	}
	SetObjectPosition(GetStoredPosition().x, GetStoredPosition().y);
}

void Player::SetColumn(int _column)
{
	switch (_column)
	{
		case 1:
		{
			m_PlayerColumn = C1;
			break;
		}	
		case 2:
		{
			m_PlayerColumn = C2;
			break;
		}
		case 3:
		{
			m_PlayerColumn = C3;
			break;
		}
		case 4:
		{
			m_PlayerColumn = C4;
			break;
		}
		case 5:
		{
			m_PlayerColumn = C5;
			break;
		}
		default:
		{
			std::cout << "INVALID COLUMN VALUE" << std::endl;
			break;
		}
	}
}