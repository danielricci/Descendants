#include "stdafx.h"
#include "Player.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(GameObject::Player, "Player");

GameObject::Player::Player(std::string texturePath, SDL_Rect* position, SDL_Rect* destination)
	: GameObject(texturePath, position, destination)
{

}

GameObject::Player::Player()
	:GameObject()
{

}

GameObject::Player::~Player()
{

}

void GameObject::Player::Update(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
			case SDLK_w:
				_destRect.y -= 1;
				break;
			case SDLK_s:
				_destRect.y += 1;
				break;
			case SDLK_a:
				_destRect.x -= 1;
				break;
			case SDLK_d:
				_destRect.x += 1;
				break;
			default:
				break;
		}
	}
}
