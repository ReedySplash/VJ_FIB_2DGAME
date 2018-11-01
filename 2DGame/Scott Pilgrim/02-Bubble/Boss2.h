#ifndef _BOSS2_INCLUDE
#define _BOSS2_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <Windows.h>
#include <cmath>
#include <iostream>

class Boss2
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void render();
	void update(int deltaTime);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	void recibirPuñetazoIzquierda();
	void recibirPatadaIzquierda();
	void recibirPuñetazoDerecha();
	void recibirPatadaDerecha();
	void recibirPuñetazoArribaDerecha();
	void recibirPuñetazoArribaIzquierda();
	bool isDying();
	bool isDeath();
	bool isCompletlyDeath();
	void free();
	void atacarPuñetazosDerecha();
	void atacarPuñetadosIzquierda();
	bool isPunchingRight();
	bool isPunchingLeft();
	bool isRecuperando();
	bool isRecibiendo();
	void turnToWalk();
	void setGolpesto0();
	void moverse(float xP, float yP);
	bool estaCerca(float xP, float yP);
	int posPlx(float xP);
	int posPly(float yP);

private:
	bool bJumping, muerto;
	int vida;
	int muriendo = 0;
	int movimiento = 0, parpadeo = 0;
	glm::fvec2 posPlayer;
	int jumpAngle, startY;
	int deltaTimeDeath, hitTime, timeAfterDeath, restablecer;
	int golpe = 0;
	TileMap *map;
	ShaderProgram mapShader;
	Texture spritesheet_enemigo, spritesheet_enemigo_left;
	Sprite *sprite_enemigo, *sprite_enemigo_left;
};

#endif