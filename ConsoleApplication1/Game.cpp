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
			case SDLK_ESCAPE: {
				_isRunning = false;
			}
							break;
			case SDLK_1: {
				_couleur = "blanc";
			}
					   break;
			case SDLK_2: {
				_couleur = "rouge";
			}
					   break;
			case SDLK_3: {
				_couleur = "vert";
			}
					   break;
			case SDLK_4: {
				_couleur = "bleu";
			}
					   break;
			case SDLK_9: {
				_modele = 1;
			}
					   break;
			case SDLK_0: {
				_modele = 2;
			}
					   break;
			default:
				break;
			}
		}
		break;
		case SDL_MOUSEBUTTONDOWN: {

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
	texturesArray = new std::array<SDL_Texture*, 8>();
	texturesArray->at(0) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle1-blanc.png").c_str()));
	texturesArray->at(1) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle1-rouge.png").c_str()));
	texturesArray->at(2) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle1-vert.png").c_str()));
	texturesArray->at(3) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle1-bleu.png").c_str()));
	texturesArray->at(4) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle2-blanc.png").c_str()));
	texturesArray->at(5) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle2-rouge.png").c_str()));
	texturesArray->at(6) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle2-vert.png").c_str()));
	texturesArray->at(7) = SDL_CreateTextureFromSurface(_screenRenderer, IMG_Load(std::string("fireworks/particle2-bleu.png").c_str()));

	if (texturesArray->at(7) != NULL)
	{
		printf(std::string("Yo tha database is ready!").c_str());
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
	generateur->Init(_screenRenderer, rand() % 20, 20 + rand() % 80, 500 + rand() % 2500, "particle" + std::to_string(_modele), _couleur, rand() % 5, rand() % 15, _position, 16, 64, 100 + rand() % 500, rand() % 90);
	_generateurs.push_back(generateur);
}