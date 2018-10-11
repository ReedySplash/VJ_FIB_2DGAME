#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level1.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 6
#define INIT_PLAYER_Y_TILES 20


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
	glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(620, 348.f) };
	pos_fin = 0.055;
	pos_ini = 0;
	initShaders();
	texCoords[0] = glm::vec2(0, 0); texCoords[1] = glm::vec2(0.055, 1);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	//texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/level1new.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	/*texs[1].loadFromFile("images/Scott-pilgrim-logo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].setMagFilter(GL_NEAREST);*/

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

}

void Level1::update(int deltaTime)
{
	currentTime += deltaTime;
	//player->update(deltaTime);
	pos_ini += 0.00005;
	pos_fin += 0.00005;
	glm::vec2 texCoords[2];
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	texCoords[0] = glm::vec2(pos_ini- 0.00005, 0); texCoords[1] = glm::vec2(pos_fin, 1);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
}

void Level1::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);
	//map->render();
	//player->render();
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

	vShader.free();
	fShader.free();
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
}



