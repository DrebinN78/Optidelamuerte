#pragma once

#include "Particule.h"
#include "Vector.h"


class GenerateurParticule
{
public:
	Particule** _liste;
	int _nbParticulesMax;
	int _nbParticulesRestantes;
	int _spawnerType;
	int _vieMin;
	int _vieMax;
	Vector _position;
	int _tailleMin;
	int _tailleMax;
	int _force;
	int _angleMax;

	~GenerateurParticule();

	void Init(int nbParticulesDebut, int nbParticulesMax, int nbParticulesTotal, int wantedType,
		int vieMin, int vieMax, Vector position, int tailleMin, int tailleMax, int force, int angleMax);

	bool EstActif();

	void AjouterParticule();

	void Update(int deltaTime);

	int GetNbParticulesActives();

	void Render(SDL_Renderer* screenRenderer);

};

