#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	music = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	gameStarted = false;
	level_1 = false;
	level_2 = false;
	level = 0;
	menu.init(music);
}

bool Game::update(int deltaTime)
{
	if (gameStarted) {
		if (!level_1 && !level_2)
		scene.update(deltaTime);
		else if (level_1) level1.update(deltaTime);
		else level2.update(deltaTime);
	}
	else if (!gameStarted) {
		if (!menuO && !menu.update(deltaTime))
			bPlay = false;
		else if (menuO) {
			menuOptions.update(deltaTime);
		}
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!gameStarted && !menuO) {
		menu.render();
	}
	else if (!gameStarted && menuO) {
		menuOptions.render();
	}
	else  {
		if (!level_1 && !level_2)
		scene.render();
		else if (level_1) level1.render();
		else level2.render();
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	if (key == 's') {
		scene.init();
		gameStarted = true;
	}
	if (key == '1') {
		level1.init(music);
		level_1 = true;
		gameStarted = true;
	}
	if (key == '2') {
		level2.init(music);
		level_2 = true;
		gameStarted = true;
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	if (key == 13 && menuO && !level_2 && !level_1) {
		menuOptions.changeMusica();
		menuOptions.playGame();
		menuOptions.showCredits();
	}
	if (key == 13 && !menuO && !level_2 && !level_1) {
		menuOptions.init(music);
		menuO = true;
	}
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	if (key == 103 && menuO) menuOptions.upOption();
	else if (key == 101 && menuO) menuOptions.downOption();
	else if (key == 100 && menuO) menuOptions.changeCharLeft();
	else if (key == 102 && menuO) menuOptions.changeCharRight();
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





