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
	pos_fin = 0.06;
	pos_ini = 0;
	initShaders();
	texCoords[0] = glm::vec2(0, 0); texCoords[1] = glm::vec2(1, 1);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, simpleTexProgram);
	texs[0].loadFromFile("images/Levels/level1new.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);

	/*player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
	player->setPosition(glm::vec2(50, 260));*/
	//player->setTileMap(map);

	enemigo1 = new Enemigo1();
	enemigo1->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
	enemigo1->setPosition(glm::vec2(250, 260));

	x = 0.f;
	projection = glm::ortho(0.f, 50.f, float(SCREEN_HEIGHT - 1), 0.f);

}

void Level1::update(int deltaTime)
{
	currentTime += deltaTime;
	//player->update(deltaTime);
	enemigo1->update(deltaTime);
	/*glm::vec2 pos = player->getPosition();
	if (pos.x > 539 && player->isWalking()) {
		x += 0.2f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
	}
	else if (pos.x < 61 && player->isWalking()) {
		x -= 0.2f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
	}
	else if (pos.x > 539 && player->isRunning()) {
		x += 0.35f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
	}
	else if (pos.x < 61 && player->isRunning()) {
		x -= 0.35f;
		projection = glm::ortho(max(0, 0 + x), max(50, 50 + x), float(SCREEN_HEIGHT - 1), 0.f);
	}
	if (x < 0) x = 0.f;*/
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
	texProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT - 1), 0.f));
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	//player->render();
	enemigo1->render();

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




