#pragma once
#include <SDL\SDL.h>
#include <glew\glew.h>
#include "Sprite.h"
#include "Error.h"
#include "GLS_Program.h"

enum class GameState {
	PLAY, EXIT
};


class MainGame
{
private:
	int _width;
	int _height;
	void init();
	SDL_Window* _window;
	Sprite _sprite;
	void processInput();
	GLS_Program _program;
public:
	MainGame();
	~MainGame();
	GameState _gamestate;
	void run();
	void draw();
	void update();
	void initShaders();
};