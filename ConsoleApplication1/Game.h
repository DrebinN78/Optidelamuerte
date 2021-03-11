#pragma once
#include <SDL_render.h>
#include <SDL_image.h>
#include "GenerateurParticule.h"
#include <string>
#include <array>
#include <vector>

class IGameEntity;

class Game
{
public:
	static enum ParticuleType
	{
		Particule1White,
		Particule1Red,
		Particule1Green,
		Particule1Blue,
		Particule2White,
		Particule2Red,
		Particule2Green,
		Particule2Blue
	};

private:
	
	ParticuleType _currentType;
    bool _isRunning;
	std::vector<GenerateurParticule*> _generateurs;
	SDL_Renderer* _screenRenderer;

public:
	static std::array<SDL_Texture*, 8>* texturesArray;
	

	Game() = default;
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;

	bool Init(SDL_Renderer* screenRenderer);

	void PopulateImageDB();

	void Release();

	void Update(int deltaTime);

	void Render(SDL_Renderer* screenRenderer);

	bool IsRunning();

	void CreerGenerateurParticule(int posX, int posY);
};

