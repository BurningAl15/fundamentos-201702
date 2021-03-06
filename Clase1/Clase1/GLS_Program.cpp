#include "GLS_Program.h"
#include <fstream>
#include <vector>

void GLS_Program::compileShader(const string& shaderpath, GLuint id) {
	string fileContent = "";
	string line = "";

	ifstream shaderFile(shaderpath);
	if (shaderFile.fail())
	{

	}
		
	while (getline(shaderFile, line))
	{
		fileContent += line + "\n";
	}
	shaderFile.close();

	const char* contents = fileContent.c_str();
	glShaderSource(id, 1, &contents, nullptr);
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		return;
	}

}

GLS_Program::GLS_Program():_programID(0),_fragmentShaderID(0),_vertexShaderID(0)
{
}


GLS_Program::~GLS_Program()
{
}


void GLS_Program::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath){
	_programID = glCreateProgram();
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if(_vertexShaderID==0)
	{ }

	_fragmentShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_fragmentShaderID == 0)
	{
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}


void GLS_Program::linkShader() {
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
		//We don't need the program anymore.
		glDeleteProgram(_programID);
		fatalError("Shaders not linked " + printf("%s", &(infoLog[0])));
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
		//Use the infoLog as you see fit.
		//In this simple program, we'll just leave
		return;
	}
	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	return;
}

void GLS_Program::addAttribute()
{

}

void GLS_Program::use() 
{
	for (int i = 0; i < _numAttribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLS_Program::unuse()
{
	for (int i = 0; i < _numAttribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}