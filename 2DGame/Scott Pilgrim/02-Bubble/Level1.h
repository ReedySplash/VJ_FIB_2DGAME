#ifndef _LEVEL1_INCLUDE
#define _LEVEL1_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Player.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <windows.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"


class Level1
{
public:
	Level1();
	~Level1();


	void init(bool music);
	void update(int deltaTime);
	void render();
private:
	bool musica;
	float currentTime;
	float pos_ini, pos_fin;
	TexturedQuad *texQuad[3];
	Texture texs[2];
	ShaderProgram simpleTexProgram;
	ShaderProgram texProgram;
	glm::mat4 projection;

	void initShaders();
};

#endif
