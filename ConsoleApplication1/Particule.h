#pragma once
#include "Vector.h"
#include "Sprite.h"


class Particule
{
public:
	Vector _position;
	Vector _force;

	Sprite* sprite;
	int vie;
	int taille;

	int vieActuelle;

	const float GRAVITE = 980;

	Particule(int wantedType, int vie, Vector _position, Vector _force, int taille);
	~Particule();

	void Update(int deltaTime);

	void Render(SDL_Renderer* screenRenderer);

	bool EstVivante();
};

