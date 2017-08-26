#include <SDL\SDL.h>
#include <glew\glew.h>

#include "MainGame.h"

int main(int argc, char** argv)
{
	MainGame game;

	game.run();

	system("Pause");

	return 0;
}