#ifndef _MENUOPTIONS_INCLUDE
#define _MENUOPTIONS_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <Windows.h>
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"

class MenuOptions
{
public:
	MenuOptions();
	~MenuOptions();
	void init(bool musica);
	void update(int deltaTime);
	void render();

private:
	int currentTime;
	int opcion;
	bool musica;

	TexturedQuad *texQuad[3];
	Texture texs[2];
	ShaderProgram simpleTexProgram;
	ShaderProgram texProgram;
	glm::mat4 projection;

	void initShaders();
};

#endif

