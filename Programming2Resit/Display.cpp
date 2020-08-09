#include "Display.h"

Display::Display()
{
	_window = nullptr;
	_screenWidth = 1024.0f;
	_screenHeight = 768.0f;
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Display::returnError(std::string errorString)
{
	int dummyVar;

	std::cout << errorString << "\n";
	std::cout << "Press any key to quit";
	std::cin >> dummyVar;
	SDL_Quit();
	
}

void Display::clearDisplay()
{
	glClearDepth(1.0); // Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::swapBuffers()
{
	SDL_GL_SwapWindow(_window);
}


float Display::GetWidth()
{
	return _screenWidth;
}
float Display::GetHeight()
{
	return _screenHeight;
}


void Display::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL); // create window

	if (_window == nullptr)
	{
		returnError("window failed to create");
	}

	glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glClearColor(0.913f, 0.462f, 0.168f, 1.0f);

}