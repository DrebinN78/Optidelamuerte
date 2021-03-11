#include "Particule.h"
#include <SDL_image.h>

Particule::Particule(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, Vector _position, Vector _force, int taille)
{
	this->vie = vie * 1000;
	this->vieActuelle = 0;
	this->_position = _position;
	this->_force = _force;
	this->taille = taille;
	//Load image at specified path
	SDL_Texture* spriteImage = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(("fireworks/" + _modele + "-" + _couleur  + ".png").c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		spriteImage = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (spriteImage == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	sprite = new Sprite(spriteImage);
}

Particule::~Particule()
{
	delete sprite;
}

void Particule::Update(int deltaTime)
{
	vieActuelle += deltaTime;
	Vector* newPosition = new Vector();
	newPosition->x = _position.x + _force.x * deltaTime / 1000;
	newPosition->y = _position.y + _force.y * deltaTime / 1000;
	_position.x = (*newPosition).x;
	_position.y = (*newPosition).y;
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
