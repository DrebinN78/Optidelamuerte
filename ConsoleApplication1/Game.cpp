#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <SDL_scancode.h>
#include "Font.h"
#include <time.h>
#include "GenerateurParticule.h"

Game::~Game() = default;

bool Game::Init(SDL_Renderer * screenRenderer)
{
	_currentType = Particule1White,
	_isRunning = true;
	_screenRenderer = screenRenderer;
	srand(time(NULL));
	PopulateImageDB();
	return true;
}

void Game::Update(int deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT: { _isRunning = false; } break;
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE: { _isRunning = false; }
			break;
			case SDLK_1 : { if (_currentType >= 4) {_currentType = Particule2White; } else { _currentType = Particule1White; } }
			break;
			case SDLK_2 : { if (_currentType >= 4) { _currentType = Particule2Red; } else { _currentType = Particule1Red; } }
			break;
			case SDLK_3 : { if (_currentType >= 4) { _currentType = Particule2Green; } else { _currentType = Particule1Green; } }
			break;
			case SDLK_4 : { if (_currentType >= 4) { _currentType = Particule2Blue; } else { _currentType = Particule1Blue; } }
			break;
			case SDLK_9: { if (_currentType >= 4) { _currentType = (ParticuleType)((int)_currentType - 4); } }
			break;
			case SDLK_0: { if (_currentType < 4) { _currentType = (ParticuleType)((int)_currentType + 4); } }
			break;
			default:
				break;
			}
		}
		break;
		case SDL_MOUSEBUTTONDOWN: 
		{

			if (e.button.button == 1)
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				CreerGenerateurParticule(mouseX, mouseY);
			}
		}
								break;
		default:
			break;
		}
	}

	if (_isRunning)
	{
		for (int i = 0; i < _generateurs.size(); i++)
		{
			_generateurs[i]->Update(deltaTime);
			if (_generateurs[i]->EstActif() == false)
			{
				auto generateur = _generateurs[i];
				_generateurs.erase(std::find(_generateurs.begin(), _generateurs.end(), generateur));
				delete generateur;
			}
		}
	}
}

void Game::PopulateImageDB()
{
	std::array<SDL_Surface*, 8> tempSurface = std::array<SDL_Surface*, 8>();
	tempSurface.at(0) = IMG_Load(std::string("fireworks/particle1-blanc.png").c_str());
	tempSurface.at(1) = IMG_Load(std::string("fireworks/particle1-rouge.png").c_str());
	tempSurface.at(2) = IMG_Load(std::string("fireworks/particle1-vert.png").c_str());
	tempSurface.at(3) = IMG_Load(std::string("fireworks/particle1-bleu.png").c_str());
	tempSurface.at(4) = IMG_Load(std::string("fireworks/particle2-blanc.png").c_str());
	tempSurface.at(5) = IMG_Load(std::string("fireworks/particle2-rouge.png").c_str());
	tempSurface.at(6) = IMG_Load(std::string("fireworks/particle2-vert.png").c_str());
	tempSurface.at(7) = IMG_Load(std::string("fireworks/particle2-bleu.png").c_str());

	texturesArray = new std::array<SDL_Texture*, 8>();
	for (int i = 0; i < 8; ++i)
	{
		texturesArray->at(i) = SDL_CreateTextureFromSurface(_screenRenderer, tempSurface.at(i));
		SDL_FreeSurface(tempSurface.at(i));
	}
}

void Game::Render(SDL_Renderer * screenRenderer)
{
	SDL_RenderClear(screenRenderer);
	if (_isRunning)
	{
		for (int i = 0; i < _generateurs.size(); i++)
		{
			_generateurs[i]->Render(screenRenderer);
		}
	}
}

void Game::Release()
{
	for (int i = 0; i < _generateurs.size(); i++)
	{
		delete _generateurs[i];
	}
	_generateurs.clear();
}

bool Game::IsRunning()
{
	return _isRunning;
}

void Game::CreerGenerateurParticule(int posX, int posY)
{
	if (_generateurs.size() == 5)
	{
		delete _generateurs[0];
		_generateurs.erase(_generateurs.begin());
	}
	Vector _position(posX, posY);
	auto generateur = new GenerateurParticule();
	generateur->Init(
		rand() % 20
		, 20 + rand() % 80
		, 500 + rand() % 2500
		, _currentType
		, rand() % 5
		, rand() % 15
		, _position
		, 16
		, 64
		, 100 + rand() % 500
		, rand() % 90);
	_generateurs.push_back(generateur);
}