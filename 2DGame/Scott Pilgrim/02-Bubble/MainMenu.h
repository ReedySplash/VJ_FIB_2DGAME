#ifndef _MAINMENU_INCLUDE
#define _MAINMENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <vector>
#include <Windows.h>
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"


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
	Texture texs[2];
	ShaderProgram simpleTexProgram;
	ShaderProgram texProgram;
	glm::mat4 projection;

	void initShaders();
	
};

#endif
