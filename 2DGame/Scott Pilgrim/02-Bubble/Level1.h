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
#include "Player.h"
#include "Enemigo1.h"
#include "Kim.h"
#include "Ramona.h"


class Level1
{
public:
	Level1();
	~Level1();


	void init(bool music);
	void update(int deltaTime);
	void render();
	void comprobarLucha(int i, glm::vec2 posPlayer);
	void comprobarAtaqueEnemigo(int i, glm::vec2 posPlayer);
private:
	bool musica;
	float currentTime;
	TexturedQuad *texQuad[3];
	Texture texs[2];
	ShaderProgram simpleTexProgram, texProgram;
	glm::mat4 projection;
	glm::ivec2 posPlayer, posEnemy;
	float x, yplayer;
	
	//Personajes dentro del juego
	int personaje; //0-2  depende del persoanje (Hay 3)
	Player *player;
	Kim *kim;
	Ramona *ramona;
	Enemigo1 *enemigo1[3];
	bool atacando[3];

	void initShaders();
};

#endif

