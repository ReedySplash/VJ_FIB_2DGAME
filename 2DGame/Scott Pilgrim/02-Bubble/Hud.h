#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE

#include "ShaderProgram.h"
#include "Sprite.h"
#include "TexturedQuad.h"
#include "Quad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Text.h"




class Hud
{
public:
	Hud();
	~Hud();
	void init(int person, ShaderProgram &shader, ShaderProgram &shader2);
	void update(int deltaTime);
	void render();
	void changeLife(int life);

private:
	int personaje, currentTime;
	float lifeInBarra,vidaInicial, currentVida;
	ShaderProgram texProgram, simpleProgram;
	TexturedQuad *texQuad[3];
	Texture texs[3];
	Quad *quad;
	Text text;
};

#endif
