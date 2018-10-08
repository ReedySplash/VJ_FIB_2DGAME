#ifndef _MAINMENU_INCLUDE
#define _MAINMENU_INCLUDE

#include <iostream>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <vector>
#include "Scene.h"
#include <windows.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "TexturedQuad.h"
#include "Quad.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



class MainMenu 
{
public:
	MainMenu();
	~MainMenu();
	void init(bool music);
	bool update(int deltTime);
	void render();


private:
	bool musica;
	float currentTime;
	TexturedQuad *texQuad[3];
	Texture texs[1];
	ShaderProgram simpleTexProgram;
	ShaderProgram texProgram;
	Quad *quad;
	glm::mat4 projection;

	void initShaders();
	
};

#endif
