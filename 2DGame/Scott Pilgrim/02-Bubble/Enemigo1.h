#ifndef _ENEMIGO1_INCLUDE
#define _ENEMIGO1_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Enemigo1
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
	bool isDeath();
	void free();
	void atacarPuñetazosDerecha();
	void atacarPuñetadosIzquierda();
	bool isPunchingRight();
	bool isPunchingLeft();
	void turnToWalk();


private:
	bool bJumping;
	int vida;
	int movimiento = 0;
	glm::fvec2 posPlayer;
	int jumpAngle, startY;
	int deltaTimeDeath, hitTime, timeAfterDeath;
	TileMap *map;
	ShaderProgram mapShader;
	Texture spritesheet_enemigo, spritesheet_enemigo_left;
	Sprite *sprite_enemigo, *sprite_enemigo_left;
};

#endif

