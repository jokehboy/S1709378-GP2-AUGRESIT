#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class Display
{
public:
	Display();
	~Display();
	void initDisplay();
	void clearDisplay();
	void swapBuffers();

	float GetWidth();
	float GetHeight();

private:
	void returnError(std::string errorString);
	SDL_Window* _window; //holds pointer to the window
	SDL_GLContext glContext;
	float _screenWidth;
	float _screenHeight;


};

