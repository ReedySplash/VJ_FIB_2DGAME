#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{	
	movimiento = 0;
	bJumping = false;
	spritesheet.loadFromFile("images/Scott quieto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(38.625, 59), glm::vec2(0.125, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.375, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.625f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.75f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.875f, 0.f));

	spritesheet_standLeft.loadFromFile("images/Scott quieto left.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_standLeft = Sprite::createSprite(glm::ivec2(38.625, 59), glm::vec2(0.125, 1), &spritesheet_standLeft, &shaderProgram);
		sprite_standLeft->setNumberAnimations(4);

		sprite_standLeft->setAnimationSpeed(STAND_LEFT, 8);
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.125, 0.f));
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.25, 0.f));
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.375, 0.f));
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.5, 0.f));
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.625f, 0.f));
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.75f, 0.f));
		sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.875f, 0.f));


	spritesheet_caminando.loadFromFile("images/0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando = Sprite::createSprite(glm::ivec2(36.833333333, 63), glm::vec2(0.1666666667, 1), &spritesheet_caminando, &shaderProgram);
	sprite_caminando->setNumberAnimations(4);


		sprite_caminando->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666666667, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333333333, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.6777777777, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.83333333333, 0.f));

	spritesheet_caminando_izq.loadFromFile("images/0_izq.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_caminando_izq = Sprite::createSprite(glm::ivec2(36.83333333, 63), glm::vec2(0.1666666667, 1), &spritesheet_caminando_izq, &shaderProgram);
		sprite_caminando_izq->setNumberAnimations(4);


		sprite_caminando_izq->setAnimationSpeed(MOVE_LEFT, 8);
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.833333333, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.6777777777, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.3333333333, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.1666666667, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	spritesheet_pegando_derecha.loadFromFile("images/atacar_puño_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_pegando_derecha = Sprite::createSprite(glm::ivec2(57, 59), glm::vec2(0.0588235294, 1), &spritesheet_pegando_derecha, &shaderProgram);
			sprite_pegando_derecha->setNumberAnimations(1);

			sprite_pegando_derecha->setAnimationSpeed(0, 12);
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.117647059, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*3.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*4.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*5.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*6.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*7.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*8.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*9.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*10.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*11.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*12.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*13.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*14.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*15.f, 0.f));
			sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.0588235294f*16.f, 0.f));

	spritesheet_pegando_izquierda.loadFromFile("images/atacar_puño_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_pegando_izquierda = Sprite::createSprite(glm::ivec2(57, 59), glm::vec2(0.0588235294, 1), &spritesheet_pegando_izquierda, &shaderProgram);
			sprite_pegando_izquierda->setNumberAnimations(1);

			sprite_pegando_izquierda->setAnimationSpeed(0, 12);
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*16.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*15.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.117647059*14.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*13.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*12.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*11.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*10.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*9.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*8.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*7.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*6.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*5.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*4.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*3.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*2.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*1.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*0.f, 0.f));

	spritesheet_saltar_derecha.loadFromFile("images/saltar_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_saltar_derecha = Sprite::createSprite(glm::ivec2(47, 67), glm::vec2(0.0769230769, 1), &spritesheet_saltar_derecha, &shaderProgram);
			sprite_saltar_derecha->setNumberAnimations(2);

			sprite_saltar_derecha->setAnimationSpeed(0, 8);
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769*2, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769*3, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769*4, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769*5, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769*6, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769*7, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 8, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 9, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 10, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 11, 0.f));
			sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 12, 0.f));

			sprite_saltar_derecha->setAnimationSpeed(1, 8);
			sprite_saltar_derecha->addKeyframe(1, glm::vec2(0.0769230769 * 10, 0.f));
			sprite_saltar_derecha->addKeyframe(1, glm::vec2(0.0769230769 * 11, 0.f));

	spritesheet_saltar_izquierda.loadFromFile("images/saltar_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_saltar_izquierda = Sprite::createSprite(glm::ivec2(47, 67), glm::vec2(0.0769230769, 1), &spritesheet_saltar_izquierda, &shaderProgram);
			sprite_saltar_izquierda->setNumberAnimations(2);

			sprite_saltar_izquierda->setAnimationSpeed(0, 8);
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769*12, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769*11, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 10, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 9, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 8, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 7, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 6, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 5, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 4, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 3, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 2, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 1, 0.f));
			sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 0, 0.f));

			sprite_saltar_izquierda->setAnimationSpeed(1, 8);
			sprite_saltar_izquierda->addKeyframe(1, glm::vec2(0.0769230769 * 11, 0.f));
			sprite_saltar_izquierda->addKeyframe(1, glm::vec2(0.0769230769 * 10, 0.f));



			
	sprite->changeAnimation(STAND_RIGHT);
	sprite_standLeft->changeAnimation(STAND_LEFT);
	sprite_caminando->changeAnimation(MOVE_RIGHT);
	sprite_caminando_izq->changeAnimation(MOVE_LEFT);
	sprite_pegando_derecha->changeAnimation(0);
	sprite_pegando_izquierda->changeAnimation(0);
	sprite_saltar_derecha->changeAnimation(0);
	sprite_saltar_izquierda->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite_caminando->update(deltaTime);
	sprite_standLeft->update(deltaTime);
	sprite_caminando_izq->update(deltaTime);
	sprite_pegando_derecha->update(deltaTime);
	sprite_pegando_izquierda->update(deltaTime);
	sprite_saltar_derecha->update(deltaTime);
	sprite_saltar_izquierda->update(deltaTime);

	if (Game::instance().getKey('x')) {
		if (movimiento == 1 || movimiento == 3 || movimiento == 4) 
			movimiento = 4;
	}

	if (Game::instance().getKey('x')) {
		if (movimiento == 0 || movimiento == 2 || movimiento == 5)
			movimiento = 5;
	}


	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (!bJumping) movimiento = 2;
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(38.625, 61)))
		{
			if (!bJumping) movimiento = 0;
			posPlayer.x += 2;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (!bJumping) movimiento = 3;
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(38.625, 61)))
		{	
			if (!bJumping) movimiento = 1;

			posPlayer.x -= 2;
		}
	}


	else
	{
		if (movimiento == 2 || movimiento == 5)
			movimiento = 0;
		else if (movimiento == 3 || movimiento == 4)
			movimiento = 1;
	}

	if (bJumping)
	{
		if (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 7)
			movimiento = 7;
		else movimiento = 6;

		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(38.625, 61), &posPlayer.y);
				if (!bJumping) {
					if (movimiento == 6) movimiento = 0;
					else movimiento = 1;
				}
			}
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(38.625, 61), &posPlayer.y))
		{
			if (movimiento == 7) movimiento = 1;
			else if (movimiento == 6) movimiento = 0;
			sprite_saltar_derecha->changeAnimation(0);
			sprite_saltar_izquierda->changeAnimation(0);
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
		else {
			if (movimiento == 7 || movimiento == 3) {
				movimiento = 7;
				sprite_saltar_derecha->changeAnimation(1);
			}
			else if (movimiento == 6 || movimiento == 2) {
				movimiento = 6;
				sprite_saltar_izquierda->changeAnimation(1);
			}
			
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x-10.f), float(tileMapDispl.y + posPlayer.y)));
	sprite_saltar_derecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - 10.f), float(tileMapDispl.y + posPlayer.y)));
	sprite_saltar_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - 10.f), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	if (movimiento == 0) sprite_standLeft->render();
	else if (movimiento == 1) sprite->render();
	else if (movimiento == 2) sprite_caminando_izq->render();
	else if (movimiento == 3) sprite_caminando->render();
	else if (movimiento == 4) sprite_pegando_derecha->render();
	else if (movimiento == 5) sprite_pegando_izquierda->render();
	else if (movimiento == 6) sprite_saltar_izquierda->render();
	else if (movimiento == 7) sprite_saltar_derecha->render();

}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}




