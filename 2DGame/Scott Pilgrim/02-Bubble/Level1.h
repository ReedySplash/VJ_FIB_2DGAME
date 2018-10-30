#ifndef _LEVEL1_INCLUDE
#define _LEVEL1_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"
#include "Player.h"
#include "Enemigo1.h"
#include "Enemigo2.h"
#include "Enemigo3.h"
#include "Kim.h"
#include "Ramona.h"
#include "Hud.h"
#include "Boss1.h"


class Level1
{
public:
	Level1();
	~Level1();


	void init(bool , int personaje);
	void update(int deltaTime);
	void render();
	void comprobarLucha(int i, glm::vec2 posPlayer, int enemigo);
	void comprobarAtaqueEnemigo(int i, glm::vec2 posPlayer, int enemigo);
	void comprobarLuchaBoss(glm::vec2 posPlayer);
	void comprobarAtaqueBoss(glm::vec2 posPlayer);
private:
	bool musica;
	float currentTime;
	TexturedQuad *texQuad[4];
	Texture texs[4];
	ShaderProgram simpleTexProgram, texProgram;
	glm::mat4 projection;
	glm::ivec2 posPlayer, posEnemy;
	float x, yplayer, y;
	glm::vec2 pos;
	
	//Personajes dentro del juego
	int personaje; //0-2  depende del persoanje (Hay 3)
	Player *player;
	Kim *kim;
	Ramona *ramona;
	Hud hud;

	//Def enemies
	Enemigo1 *enemigo1[3];
	Enemigo2 *enemigo2[3];
	Enemigo3 *enemigo3[3];
	Boss1 *boss;
	bool atacando1[3];
	bool atacando2[3];
	bool atacando3[3];
	bool atacando_boss;
	void initShaders();
};

#endif

