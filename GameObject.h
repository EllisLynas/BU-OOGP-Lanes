#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>
#include <ctime>

class GameObject
{
public:
	virtual void LoadObject(std::string _filename);
	virtual void DrawObject(sf::RenderWindow & _window);
	virtual void SetObjectPosition(float _x, float _y);
	virtual void SetPosition(float _x, float _y);
	virtual sf::Vector2f GetPosition();
	sf::Vector2f GetStoredPosition();
	sf::Sprite& GetSprite();
	bool HasLoaded();
	virtual void Scroll(float _speed);

	GameObject();
	~GameObject();

private:
	sf::Vector2f m_Position;
	sf::Sprite  m_Sprite;
	sf::Texture m_Texture;
	std::string m_Filename;
	bool m_HasLoaded;
};