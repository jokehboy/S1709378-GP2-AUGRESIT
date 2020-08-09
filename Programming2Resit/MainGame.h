#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Audio.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame();
	~MainGame();

	float counter;

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	void collectCroissant(glm::vec3 playerPos, float playerCollRadius, glm::vec3 croissantPos, float croissantCollRadius);
	void giveCroissant(glm::vec3 carlPos, float carlCollRad, glm::vec3 playerPos, float playerCollRadius);

	void PlayAudioAtStart();
	void PlayCollectedCroissant();
	void PlayGivenCroissant();


	

	Display _gameDisplay;
	GameState _gameState;
	Mesh carlModel;
	Mesh tableModel;
	Mesh croissantModel;
	Camera camera;
	
	Audio audio;

	unsigned int carlIntro;
	unsigned int carlCollectedCroissant;
	unsigned int carlGivenCroissant;
	unsigned int successNoise;
	unsigned int backgroundMusic;

	



};

