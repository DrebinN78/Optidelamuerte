#include "Particule.h"
#include "Game.h"
#include <SDL_image.h>

Particule::Particule(int wantedType, int vie, Vector _position, Vector _force, int taille)
{
	this->vie = vie * 1000;
	this->vieActuelle = 0;
	this->_position = _position;
	this->_force = _force;
	this->taille = taille;
	sprite = new Sprite(Game::GetTextureArray()->at(wantedType));
}

Particule::~Particule()
{
	this->sprite = nullptr;
}

void Particule::Update(int deltaTime)
{
	vieActuelle += deltaTime;
	_position.x += _force.x * deltaTime / 1000;
	_position.y += _force.y * deltaTime / 1000;
	//gravité
	_force.y += deltaTime * GRAVITE / 1000;
	//rebond
	if (_position.y + taille / 2 >= 720)
	{
		_position.y = 720 - (_position.y - 720);
		_force.y = -_force.y * 0.8;
	}
}

void Particule::Render(SDL_Renderer* screenRenderer)
{
	unsigned char alpha = 0;
	if (vie > vieActuelle)
		alpha = (255 * (vie - vieActuelle)) / vie;
	sprite->Render(screenRenderer, _position.x, _position.y, taille, taille, alpha);
}

bool Particule::EstVivante()
{
	if (vie > vieActuelle)
		return true;
	return false;
}
