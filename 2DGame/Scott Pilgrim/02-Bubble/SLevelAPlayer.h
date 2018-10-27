#pragma once

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <Windows.h>
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"
#include "Text.h"
#include <iostream>
#include <vector>
class SLevelAPlayer
{
public:
	SLevelAPlayer();
	~SLevelAPlayer();
	void init(ShaderProgram &simpleTexProgram, ShaderProgram &texProgram);
	void update(int deltaTime);
	void render();
	void right();
	void left();

private:
	int currentTime;
	int opcion;
	bool musica;

	TexturedQuad *texQuad[3];
	Texture texs[2];
	ShaderProgram simpleTexProgram;
	ShaderProgram texProgram;
	glm::mat4 projection;
	Text text;
	string personaje_name;
	int personaje, level_num;


	Texture spritesheet_Scott;
	Texture spritesheet_Kim;
	Texture spritesheet_Ramona;

	Sprite *sprite_Scott;
	Sprite *sprite_Kim;
	Sprite *sprite_Ramona;

	void initShaders();
};

