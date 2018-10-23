#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
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
	void recibirPuñetazoDerecha();
	void recibirPuñetazoIzquierda();

	
private:
	bool bJumping;
	int level;
	float tiempoAtacandoPuñetazo;
	int movimiento, tiempoPatada;
	float posLevel;
	bool puñetazo, patada, puñetazo_aux, patada_aux;;
	int xpuñetazo;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Texture spritesheet_caminando;
	Texture spritesheet_caminando_izq;
	Texture spritesheet_standLeft;
	Texture spritesheet_pegando_derecha;
	Texture spritesheet_pegando_izquierda;
	Texture spritesheet_saltar_izquierda;
	Texture spritesheet_saltar_derecha;
	Texture spritesheet_patada_izquierda;
	Texture spritesheet_patada_derecha;
	Texture spritesheet_correr;
	Texture spritesheet_recibir_golpe;
	Texture spritesheet_puñetazo_arriba;
	Texture spritesheet_puñetazo_arriba_izq;
	Sprite *sprite;
	Sprite *sprite_caminando;
	Sprite *sprite_caminando_izq;
	Sprite *sprite_standLeft;
	Sprite *sprite_pegando_derecha;
	Sprite *sprite_pegando_izquierda;
	Sprite *sprite_saltar_izquierda;
	Sprite *sprite_saltar_derecha;
	Sprite *sprite_patada_izquierda;
	Sprite *sprite_patada_derecha;
	Sprite *sprite_correr;
	Sprite *recibir_golpe;
	Sprite *puñetazo_arriba;
	Sprite *puñetazo_arriba_izq;
	TileMap *map;
	ShaderProgram mapShader;

};


#endif // _PLAYER_INCLUDE


