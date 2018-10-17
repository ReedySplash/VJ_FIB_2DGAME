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


private:
	bool bJumping;
	int movimiento = 0;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	TileMap *map;
	ShaderProgram mapShader;
	Texture spritesheet_enemigo, spritesheet_enemigo_right;
	Sprite *sprite_enemigo, *sprite_enemigo_right;
};

#endif

