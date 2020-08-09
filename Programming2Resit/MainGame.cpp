#include "MainGame.h"
#include <iostream>
#include <string>
#include "Camera.h"


bool introPlayed = false;
glm::vec3 cameraPos;
glm::vec3 cameraLook;

bool croissantCollected = false;
bool collectedPlayed = false;
bool croissantGiven = false;
bool givenPlayed = false;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display();
	Mesh* carlModel();
	Mesh* tableModel();
	Mesh* croissantModel();
	Audio* audio();
	
	
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();



}



void MainGame::PlayAudioAtStart()
{
	if (introPlayed == false)
	{
		
		audio.playSound(carlIntro);
		introPlayed = true;
	}
}


void MainGame::PlayCollectedCroissant()
{
	
	if (croissantCollected == true && !collectedPlayed)
	{
		audio.stopSound(carlIntro);
		audio.playSound(carlCollectedCroissant);
		collectedPlayed = true;
	}

	

}

void MainGame::PlayGivenCroissant()
{
	
	if (croissantCollected == true && croissantGiven == true && !givenPlayed)
	{
		audio.stopSound(carlCollectedCroissant);
		audio.playSound(carlGivenCroissant);
		givenPlayed = true;
	}
}


void MainGame::initSystems()
{
	_gameDisplay.initDisplay();



	carlIntro = audio.loadSound("..\\res\\Audio\\CarlIntro.wav");
	carlCollectedCroissant = audio.loadSound("..\\res\\Audio\\CarlPickedUpCroissant.wav");
	carlGivenCroissant = audio.loadSound("..\\res\\Audio\\GaveCarlCroissant.wav");
	backgroundMusic = audio.loadSound("..\\res\\Audio\\BeetorOffAlone.wav");

	carlModel.loadModel("..\\res\\Models\\Carl\\carl.obj");
	tableModel.loadModel("..\\res\\Models\\Table_Carre.obj");
	croissantModel.loadModel("..\\res\\Models\\Croissant.obj");

	camera.initCamera(glm::vec3(0, 0, -120), 70.0f, (float)_gameDisplay.GetWidth() / _gameDisplay.GetHeight(), 0.01f, 10000.0f);

	counter = 0.0f;
	audio.playSound(backgroundMusic);
	PlayAudioAtStart();
}




void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collectCroissant(camera.getCameraPosition(), 0.2f, croissantModel.getMeshColliderPosition(), croissantModel.getMeshColliderRadius());
		giveCroissant(carlModel.getMeshColliderPosition(), carlModel.getMeshColliderRadius(), camera.getCameraPosition(), 0.2f);
	}
}

void MainGame::processInput()
{
	SDL_Event keyInput;

	while (SDL_PollEvent(&keyInput))
	{
		switch (keyInput.type)
		{
			//Checking if a key is pressed
		case SDL_KEYDOWN:
			switch (keyInput.key.keysym.sym)
			{
				//Checks if the key is being pressed and moving the appropriate mesh / camera. Also used to end the game
			case SDLK_d:
			{
				camera.moveRight(0.1f);
				
			}
			break;
			case SDLK_a:
			{
				camera.moveLeft(0.1f);
			}
			break;
			case SDLK_w:
			{
				camera.moveForward(0.1f);
			}
			break;
			case SDLK_s:
			{
				camera.moveBackwards(0.1f);

			}
			break;
			case SDLK_UP:
			{
				camera.moveUp(0.1f);
			}
			break;
			case SDLK_DOWN:
			{
				camera.moveDown(0.1f);
			}
			break;
			case SDLK_LEFT:
			{
				camera.Yaw(0.2f);
			}
			break;
			case SDLK_RIGHT:
			{
				camera.Yaw(-0.2f);
			}
			break;
			case SDLK_ESCAPE:
			{
				_gameState = GameState::EXIT;
			}

			}
		}

		
	}

}


void MainGame::collectCroissant(glm::vec3 playerPos, float playerCollRadius, glm::vec3 croissantPos, float croissantCollRadius)
{
	float distance = glm::sqrt((croissantPos.x - playerPos.x)*(croissantPos.x - playerPos.x) + (croissantPos.y - playerPos.y)*(croissantPos.y - playerPos.y) + (croissantPos.z - playerPos.z)*(croissantPos.z - playerPos.z));

	if (distance < (playerCollRadius + croissantCollRadius))
	{
		printf("colliding");
		croissantCollected = true;
		PlayCollectedCroissant();
	}
}


void MainGame::giveCroissant(glm::vec3 carlPos, float carlCollRad, glm::vec3 playerPos, float playerCollRadius)
{
	float distance = glm::sqrt((carlPos.x - playerPos.x)*(carlPos.x - playerPos.x) + (carlPos.y - playerPos.y)*(carlPos.y - playerPos.y) + (carlPos.z - playerPos.z)*(carlPos.z - playerPos.z));

	if (distance < (playerCollRadius + carlCollRad) && croissantCollected == true)
	{
		croissantGiven = true;
		PlayGivenCroissant();
	}

}



void MainGame::drawGame()
{
	_gameDisplay.clearDisplay();

	Shader shader("..\\res\\shader"); //new shader
	Texture carlTex("..\\res\\Models\\Water.jpg"); //load texture
	Texture tableTex("..\\res\\Models\\Wood.jpg");
	Texture croissantTex("..\\res\\Models\\BreadTex.jpg");
	Transform transform;

	transform.SetPos(glm::vec3(0, 0,-100));

	if (croissantCollected == false)
	{
		transform.SetRot(glm::vec3(0.0, counter * 2, sinf(counter * 1) * 10));
	}
	if (croissantCollected == true)
	{
		transform.SetRot(glm::vec3(0.0, counter * 2, sinf(counter * 1) * 10));
	}
	if (croissantCollected == true && croissantGiven == true)
	{
		transform.SetRot(glm::vec3(0.0, counter * 4, sinf(counter * 3) * 50));

	}
	
	transform.SetScale(glm::vec3(3, 3, 3));

	shader.Bind();
	shader.Update(transform, camera);
	carlTex.Bind(0);
	carlModel.Draw();
	carlModel.updateCollider(*transform.GetPos(), 4.0f);

	transform.SetPos(glm::vec3(-6, -3, -100));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(.05, .05, .05));

	shader.Bind();
	shader.Update(transform, camera);
	tableTex.Bind(0);
	tableModel.Draw();
	

	transform.SetPos(glm::vec3(-6, -0.75, -100.25));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	if (croissantCollected == true)
	{
		transform.SetScale(glm::vec3(0, 0, 0));
	}
	else
	{
		transform.SetScale(glm::vec3(.1, .1, .1));
	}
	

	shader.Bind();
	shader.Update(transform, camera);
	croissantTex.Bind(0);
	croissantModel.Draw();
	croissantModel.updateCollider(*transform.GetPos(), 1.0f);


	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffers();

}
