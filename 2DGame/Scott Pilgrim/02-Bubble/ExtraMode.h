#ifndef _EXTRAMODE_INCLUDE
#define _EXTRAMODE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <vector>
#include <Windows.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"
#include "Player.h"
#include "Ramona.h"
#include "Hud.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class ExtraMode
{
public:
	ExtraMode();
	~ExtraMode();
	void init(bool music);
	bool update(int deltTime);
	void render();
	void comprobarLucha();


private:
	bool musica, jumping, jumping2, atacando, atacando_ra;
	float currentTime, y, y_ramona;
	TexturedQuad *texQuad[2];
	Texture texs[2];
	ShaderProgram simpleTexProgram;
	ShaderProgram texProgram;
	glm::mat4 projection;

	Player *player;
	Ramona *ramona;
	Hud hud, hud2;
	void initShaders();

};

#endif

