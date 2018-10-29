#ifndef _RAMONA_INCLUDE
#define _RAMONA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Ramona
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int level);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	float getPosLevel();
	bool isWalking();
	bool isRunning();
	bool isKicking_left();
	bool isKicking_right();
	bool isPunching_left();
	bool isPunching_right();
	bool isPunching_up_left();
	bool isPunching_up_right();
	bool isRecuperando();
	bool isJumping();
	void recibirPuñetazoDerecha();
	void recibirPuñetazoIzquierda();
	void turnToWalk();
	int getVida();

private:
	bool bJumping;
	int level;
	bool derecha;
	int movimiento = 0, tiempoPatada;
	float posLevel;
	glm::fvec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Texture spritesheet_caminando;
	Texture spritesheet_caminando_izq;
	Texture spritesheet_standLeft;
	Texture spritesheet_pegando_derecha;
	Texture spritesheet_pegando_izquierda;
	Texture spritesheet_saltar_izquierda;
	Texture spritesheet_saltar_derecha;
	Texture spritesheet_rayo_izquierda;
	Texture spritesheet_rayo_derecha;
	Texture spritesheet_correr;
	Texture spritesheet_correr_iz;
	Texture spritesheet_recibir_golpe;
	Texture spritesheet_martillo;
	Texture spritesheet_martillo_izq;
	Texture spritesheet_recibir_daño;
	Texture spritesheet_recibir_daño_izq;
	Sprite *sprite;
	Sprite *sprite_caminando;
	Sprite *sprite_caminando_izq;
	Sprite *sprite_standLeft;
	Sprite *sprite_pegando_derecha;
	Sprite *sprite_pegando_izquierda;
	Sprite *sprite_saltar_izquierda;
	Sprite *sprite_saltar_derecha;
	Sprite *sprite_rayo_izquierda;
	Sprite *sprite_rayo_derecha;
	Sprite *sprite_correr;
	Sprite *sprite_correr_iz;
	Sprite *recibir_golpe;
	Sprite *sprite_martillo;
	Sprite *sprite_martillo_iz;
	Sprite *sprite_recibir;
	Sprite *sprite_recibir_izq;
	TileMap *map;
	ShaderProgram mapShader;

	int vida;
	int hits;
	float recuperando;
	int posIni, posFin;
};


#endif // _RAMONA_INCLUDE



