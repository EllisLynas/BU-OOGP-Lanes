#include "GameObject.h"

GameObject::GameObject()
{
	m_HasLoaded = false;

	// SEED RANDOM GENERATOR
	time_t qTime;
	time(&qTime);
	srand(qTime);
	srand(time(NULL));
}

GameObject::~GameObject()
{
}

void GameObject::LoadObject(std::string _filename)
{
	if (m_Texture.loadFromFile(_filename) == false)
	{
		m_Filename = "";
		m_HasLoaded = false;
	}
	else
	{
		m_Filename = _filename;
		m_Sprite.setTexture(m_Texture);
		m_HasLoaded = true;
	}
}

void GameObject::DrawObject(sf::RenderWindow & _window)
{
	if (m_HasLoaded)
	{
		_window.draw(m_Sprite);
	}
	else
	{
		std::cout << "DEBUG: SPRITE NOT LOADED ( DRAW OBJECT )" << std::endl;
	}
}

// SETS OBJECT POSITION AND ORIGIN
void GameObject::SetObjectPosition(float _x, float _y)
{
	if (m_HasLoaded)
	{
		m_Position = sf::Vector2f(_x, _y);
		m_Sprite.setOrigin(m_Texture.getSize().x / 2, m_Texture.getSize().y / 2);
		m_Sprite.setPosition(m_Position.x, m_Position.y);
	}
	else
	{
		std::cout << "DEBUG: SPRITE NOT LOADED ( SET POSITION )" << std::endl;
	}
}

// SETS POSITION OF OBJECT WITH AN ORIGIN ALREADY DEFINED
void GameObject::SetPosition(float _x, float _y)
{
	if (m_HasLoaded)
	{
		m_Position = sf::Vector2f(_x, _y);
		m_Sprite.setPosition(_x, _y);
	}
}

// GETS THE OBJECTS POSITION ON SCREEN IN REAL-TIME
sf::Vector2f GameObject::GetPosition()
{
	if (m_HasLoaded)
	{
		return m_Sprite.getPosition();
	}
	return sf::Vector2f();
}

// GETS THE OBJECTS POSITION FROM ITS ATTRIBUTES
sf::Vector2f GameObject::GetStoredPosition()
{
	return m_Position;
}

// USED TO GET SPRITE (USED IN DETECTING COLLISIONS)
sf::Sprite& GameObject::GetSprite()
{
	return m_Sprite;
}

bool GameObject::HasLoaded()
{
	return m_HasLoaded;
}

// INTERPOLATE Y VALUE (USED FOR LINES)
void GameObject::Scroll(float _speed)
{
	float PosX = GetStoredPosition().x;
	float PosY = GetStoredPosition().y + _speed;
	SetObjectPosition(PosX, PosY);
}