#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <vector>
#include <Windows.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Instructions
{
public:
	Instructions();
	~Instructions();
	void init(ShaderProgram &prog);
	bool update(int deltTime);
	void render();


private:
	bool musica;
	float currentTime;
	TexturedQuad *texQuad[3];
	Texture texs[2];
	ShaderProgram texProgram;
	glm::mat4 projection;

};

#endif
