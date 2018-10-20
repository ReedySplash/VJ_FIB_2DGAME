#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level1.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 50
#define INIT_PLAYER_Y_TILES 150


Level1::Level1()
{
	//player = NULL;
}

Level1::~Level1()
{
	/*if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;*/
}


void Level1::init(bool music)
{
	if(music) {
		mciSendString(TEXT("stop sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/20.mp3 repeat"), NULL, 0, NULL);
	}
	else {
		//	mciSendString(TEXT("stop sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("stop sounds/SOUND/20.mp3"), NULL, 0, NULL);
	}
	musica = music;
	currentTime = 0.0f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(620, 340.f) };
	initShaders();
	texCoords[0] = glm::vec2(0, 0); texCoords[1] = glm::vec2(1, 1);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, simpleTexProgram);
	texs[0].loadFromFile("images/Levels/level1new.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	personaje = 0;

	//Init jugador, depende del elegido
	if (personaje == 0) {
		//Init player
		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram, 1);
		player->setPosition(glm::vec2(65, 260));
		//player->setTileMap(map);
	}

	else if (personaje == 1) {
		kim = new Kim();
		kim->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
		kim->setPosition(glm::vec2(65, 260));
	}

	//Init Enemigos
	for (int i = 0; i < 1; ++i) {
		enemigo1[i] = new Enemigo1();
		enemigo1[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
		enemigo1[i]->setPosition(glm::vec2(150, 260));
	}

	x = 0.f;
	projection = glm::ortho(0.f, 50.f, float(SCREEN_HEIGHT - 1), 0.f);

}

void Level1::update(int deltaTime)
{
	currentTime += deltaTime;
	glm::vec2 pos;
	bool isWalking, isRunning;
	if (personaje == 0) {
		player->update(deltaTime);
		pos = player->getPosition();
		isWalking = player->isWalking();
		isRunning = player->isRunning();
	}
	else if (personaje == 1) {
		kim->update(deltaTime);
		pos = kim->getPosition();
		isWalking = kim->isWalking();
		isRunning = kim->isRunning();
	}

	if (pos.x > 539 && isWalking) {
		x += 0.2f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
		for (int i = 0; i < 1; ++i) {
			if (!enemigo1[i]->isDeath()) {
				glm::vec2 pose = enemigo1[i]->getPosition();
				pose.x -= 2.57f;
				enemigo1[i]->setPosition(pose);
			}
		}
	}
	else if (pos.x < 61 && isWalking) {
		x -= 0.2f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
		for (int i = 0; i < 1; ++i) {
			if (!enemigo1[i]->isDeath()) {
				glm::vec2 pose = enemigo1[i]->getPosition();
				if (x > 0) pose.x += 2.57f;
				enemigo1[i]->setPosition(pose);
			}
		}
	}
	else if (pos.x > 539 && isRunning) {
		x += 0.35f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
		for (int i = 0; i < 1; ++i) {
			if (!enemigo1[i]->isDeath()) {
				glm::vec2 pose = enemigo1[i]->getPosition();
				pose.x -= 2.6f*1.725f;
				enemigo1[i]->setPosition(pose);
			}
		}
	}
	else if (pos.x < 61 && isRunning) {
		x -= 0.35f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
		for (int i = 0; i < 1; ++i) {
			if (!enemigo1[i]->isDeath()) {
				glm::vec2 pose = enemigo1[i]->getPosition();
				if (x > 0) pose.x += 2.6f*1.725f;
				enemigo1[i]->setPosition(pose);
			}
		}
	}
	if (x <= 0) x = 0.f;
	for (int i = 0; i < 1; ++i) {
		comprobarLucha(i, pos);
		enemigo1[i]->update(deltaTime);
	}
}

void Level1::render()
{
	glm::mat4 modelview;

	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);
	//map->render();


	texProgram.use();
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT - 1), 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	//texProgram.setUniformMatrix4f("projection", glm::ortho(0.f + x * 12.8f, float(SCREEN_WIDTH) + x * 12.8f, float(SCREEN_HEIGHT - 1), 0.f));
	for (int i = 0; i < 1; ++i) {
		if (!enemigo1[i]->isDeath()) enemigo1[i]->render();
		else enemigo1[i]->free();
	}
	//texProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT - 1), 0.f));
	if (personaje == 0) player->render();
	else if (personaje == 1) kim->render();
	
	

}

void Level1::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}

	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	simpleTexProgram.init();
	simpleTexProgram.addShader(vShader);
	simpleTexProgram.addShader(fShader);
	simpleTexProgram.link();
	if (!simpleTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleTexProgram.log() << endl << endl;
	}
	simpleTexProgram.bindFragmentOutput("outColor");
}


void Level1::comprobarLucha(int i, glm::vec2 posPlayer) {
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right;
	if (personaje == 0) {
		isPunching_left = player->isPunching_left();
		isPunching_right = player->isPunching_right();
		isKicking_left = player->isKicking_left();
		isKicking_right = player->isKicking_right();
	}
	else if (personaje == 1) {
		isPunching_left = kim->isPunching_left();
		isPunching_right = kim->isPunching_right();
		isKicking_left = kim->isKicking_left();
		isKicking_right = kim->isKicking_right();
	}
	posEnemy = enemigo1[i]->getPosition();
	if ((posPlayer.x <= (posEnemy.x + 90) && (posPlayer.x - 40 > posEnemy.x)) && (posPlayer.y <= posEnemy.y + 15 && posPlayer.y >= posEnemy.y - 15)) {
		if (isPunching_left) {
			enemigo1[i]->recibirPuñetazoDerecha();
		}

		else if (isKicking_left) {
			enemigo1[i]->recibirPatadaDerecha();
		}
	}

	else if ((posPlayer.x >= posEnemy.x - 20 && posPlayer.x < posEnemy.x+20) && (posPlayer.y <= posEnemy.y + 15 && posPlayer.y >= posEnemy.y - 15)) {
		if (isPunching_right) {
			enemigo1[i]->recibirPuñetazoIzquierda();
		}

		else if (isKicking_right) {
			enemigo1[i]->recibirPatadaIzquierda();
		}
	}
}




