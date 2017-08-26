#pragma once

#include <glew\glew.h>

class Sprite {
private:
	float x;
	float y;
	int _width;
	int _height;

	GLuint _vobID;//vertex buffer object

public:
	Sprite();
	~Sprite();
	void init(float x, float y, int width, int height);
	void draw();

};