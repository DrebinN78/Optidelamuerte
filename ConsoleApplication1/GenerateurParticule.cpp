#include "GenerateurParticule.h"
#include "Game.h"

GenerateurParticule::~GenerateurParticule()
{
	delete[] _liste;
}

void GenerateurParticule::Init(int nbParticulesDebut, int nbParticulesMax, int nbParticulesTotal, Game::ParticuleType wantedType, int vieMin, int vieMax, Vector position, int tailleMin, int tailleMax, int force, int angleMax)
{
	this->_nbParticulesMax = nbParticulesMax;
	this->_nbParticulesRestantes = nbParticulesTotal;
	this->_spawnerType = wantedType;
	this->_vieMin = vieMin;
	this->_vieMax = vieMax;
	this->_position = position;
	this->_tailleMin = tailleMin;
	this->_tailleMax = tailleMax;
	this->_force = force;
	this->_angleMax = angleMax;

	_liste = new Particule * [_nbParticulesMax];
	for (int i = 0; i < _nbParticulesMax; i++)
	{
		_liste[i] = nullptr;
	}

	for (int i = 0; i < nbParticulesDebut; i++)
	{
		AjouterParticule();
		_nbParticulesRestantes--;
	}
}

bool GenerateurParticule::EstActif()
{
	if (_nbParticulesRestantes > 0)
		return true;
	return false;
}

void GenerateurParticule::AjouterParticule()
{
	for (int i = 0; i < _nbParticulesMax; i++)
	{
		if (_liste[i] == nullptr)
		{
			int angle = 0;
			if (_angleMax != 0)
				angle = rand() % _angleMax;
			if (rand() % 2 == 1)
				angle = -angle;
			int vie = _vieMin;
			if (_vieMin != _vieMax)
				vie = _vieMin + rand() % (_vieMax - _vieMin);
			int taille = _tailleMin;
			if (_tailleMin != _tailleMax)
				taille = _tailleMin + rand() % (_tailleMax - _tailleMin);
			Vector forceVec(-_force * sin(angle), _force * cos(angle));
			_liste[i] = new Particule(_spawnerType, vie, _position, forceVec, taille);
			return;
		}
	}
}

void GenerateurParticule::Update(int deltaTime)
{
	for (int i = 0; i < _nbParticulesMax; i++)
	{
		if (_liste[i] != nullptr)
		{
			_liste[i]->Update(deltaTime);
			if (_liste[i]->EstVivante() == false)
			{
				delete _liste[i];
				for (int j = i; j < _nbParticulesMax - 1; j++)
				{
					_liste[j] = _liste[j + 1];
				}
				_liste[_nbParticulesMax - 1] = nullptr;
			}
		}
	}
	if (GetNbParticulesActives() < _nbParticulesMax && EstActif())
	{
		AjouterParticule();
		_nbParticulesRestantes--;
	}
}

int GenerateurParticule::GetNbParticulesActives()
{
	int nb = 0;
	for (int i = 0; i < _nbParticulesMax; i++)
	{
		if (_liste[i] != nullptr)
		{
			nb = nb + 1;
		}
	}
	return nb;
}

void GenerateurParticule::Render(SDL_Renderer* screenRenderer)
{
	for (int i = 0; i < _nbParticulesMax; i++)
	{
		if (_liste[i] != nullptr)
		{
			_liste[i]->Render(screenRenderer);
		}
	}
}
