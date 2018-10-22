#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Kim.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


Kim::Kim()
{
}


Kim::~Kim()
{
}


void Kim::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	mapShader = shaderProgram;
	movimiento = 0;
	bJumping = false;
	spritesheet.loadFromFile("images/Kim/Kim_stand_right.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(35, 90), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.75, 0.f));

	spritesheet_standLeft.loadFromFile("images/Kim/Kim_stand_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_standLeft = Sprite::createSprite(glm::ivec2(35, 90), glm::vec2(0.25, 1), &spritesheet_standLeft, &shaderProgram);
	sprite_standLeft->setNumberAnimations(4);

	sprite_standLeft->setAnimationSpeed(STAND_LEFT, 8);
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.75, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.5, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.25, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0, 0.f));
	


	spritesheet_caminando.loadFromFile("images/Kim/Kim_walk_right.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando = Sprite::createSprite(glm::ivec2(38, 90), glm::vec2(0.1666666667, 1), &spritesheet_caminando, &shaderProgram);
	sprite_caminando->setNumberAnimations(4);


	sprite_caminando->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666666667, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333333333, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.6777777777, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.83333333333, 0.f));

	spritesheet_caminando_izq.loadFromFile("images/Kim/Kim_walk_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando_izq = Sprite::createSprite(glm::ivec2(38, 90), glm::vec2(0.1666666667, 1), &spritesheet_caminando_izq, &shaderProgram);
	sprite_caminando_izq->setNumberAnimations(4);


	sprite_caminando_izq->setAnimationSpeed(MOVE_LEFT, 8);
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.833333333, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.6777777777, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.3333333333, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.1666666667, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	spritesheet_pegando_derecha.loadFromFile("images/Kim/Kim_puñetazos_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_pegando_derecha = Sprite::createSprite(glm::ivec2(57, 100), glm::vec2(0.0833333333, 1), &spritesheet_pegando_derecha, &shaderProgram);
	sprite_pegando_derecha->setNumberAnimations(1);

	sprite_pegando_derecha->setAnimationSpeed(0, 10);
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333 *2, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*3.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*4.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*5.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*6.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*7.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*8.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*9.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*10.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333*11.f, 0.f));
	

	spritesheet_pegando_izquierda.loadFromFile("images/Kim/Kim_puñetazos_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_pegando_izquierda = Sprite::createSprite(glm::ivec2(57, 100), glm::vec2(0.083333333, 1), &spritesheet_pegando_izquierda, &shaderProgram);
	sprite_pegando_izquierda->setNumberAnimations(1);

	sprite_pegando_izquierda->setAnimationSpeed(0, 10);
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*11.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*10.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*9.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*8.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*7.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*6.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*5.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*4.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*3.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*2.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*1.f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.083333333*0.f, 0.f));

	spritesheet_saltar_derecha.loadFromFile("images/Kim/Kim_jump_right.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_saltar_derecha = Sprite::createSprite(glm::ivec2(50, 100), glm::vec2(0.0769230769, 1), &spritesheet_saltar_derecha, &shaderProgram);
	sprite_saltar_derecha->setNumberAnimations(2);

	sprite_saltar_derecha->setAnimationSpeed(0, 8);
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 2, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 3, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 4, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 5, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 6, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 7, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 8, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 9, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 10, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 11, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.0769230769 * 12, 0.f));

	sprite_saltar_derecha->setAnimationSpeed(1, 8);
	sprite_saltar_derecha->addKeyframe(1, glm::vec2(0.0769230769 * 10, 0.f));
	sprite_saltar_derecha->addKeyframe(1, glm::vec2(0.0769230769 * 11, 0.f));

	spritesheet_saltar_izquierda.loadFromFile("images/Kim/Kim_jump_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_saltar_izquierda = Sprite::createSprite(glm::ivec2(50, 100), glm::vec2(0.0769230769, 1), &spritesheet_saltar_izquierda, &shaderProgram);
	sprite_saltar_izquierda->setNumberAnimations(2);

	sprite_saltar_izquierda->setAnimationSpeed(0, 8);
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 12, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.0769230769 * 11, 0.f));
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
	sprite_saltar_izquierda->addKeyframe(1, glm::vec2(0.0769230769 * 2, 0.f));
	sprite_saltar_izquierda->addKeyframe(1, glm::vec2(0.0769230769 * 1, 0.f));

	spritesheet_patada_derecha.loadFromFile("images/Kim/Kim_patada_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_patada_derecha = Sprite::createSprite(glm::ivec2(65, 100), glm::vec2(0.142857143, 1), &spritesheet_patada_derecha, &shaderProgram);
	sprite_patada_derecha->setNumberAnimations(1);

	sprite_patada_derecha->setAnimationSpeed(0, 12);
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143*2, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143*3, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143*4, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143*5, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143*6, 0.f));

	spritesheet_patada_izquierda.loadFromFile("images/Kim/Kim_patada_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_patada_izquierda = Sprite::createSprite(glm::ivec2(65, 100), glm::vec2(0.142857143, 1), &spritesheet_patada_izquierda, &shaderProgram);
	sprite_patada_izquierda->setNumberAnimations(1);

	sprite_patada_izquierda->setAnimationSpeed(0, 12);
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143*6, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143*5, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143*4, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143*3, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143*2, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0, 0.f));





	sprite->changeAnimation(STAND_RIGHT);
	sprite_standLeft->changeAnimation(STAND_LEFT);
	sprite_caminando->changeAnimation(MOVE_RIGHT);
	sprite_caminando_izq->changeAnimation(MOVE_LEFT);
	sprite_pegando_derecha->changeAnimation(0);
	sprite_pegando_izquierda->changeAnimation(0);
	sprite_saltar_derecha->changeAnimation(0);
	sprite_saltar_izquierda->changeAnimation(0);
	sprite_patada_derecha->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Kim::update(int deltaTime)
{
	/*sprite->update(deltaTime);
	sprite_caminando->update(deltaTime);
	sprite_standLeft->update(deltaTime);
	sprite_caminando_izq->update(deltaTime);
	sprite_pegando_derecha->update(deltaTime);
	sprite_pegando_izquierda->update(deltaTime);
	sprite_saltar_derecha->update(deltaTime);
	sprite_saltar_izquierda->update(deltaTime);
	sprite_patada_derecha->update(deltaTime);
	sprite_patada_izquierda->update(deltaTime);

	if (Game::instance().getKey('x') && (movimiento == 1 || movimiento == 3 || movimiento == 4)) {
		movimiento = 4;
	}

	else if (Game::instance().getKey('x') && (movimiento == 0 || movimiento == 2 || movimiento == 5)) {
		movimiento = 5;
	}

	else if (Game::instance().getKey('c') && (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 9)) {
		if (movimiento != 9)sprite_patada_derecha->changeAnimation(0);
		movimiento = 9;
	}

	else if (Game::instance().getKey('c') && (movimiento == 0 || movimiento == 2 || movimiento == 5 || movimiento == 8)) {
		if (movimiento != 8)sprite_patada_izquierda->changeAnimation(0);
		movimiento = 8;
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
		if (movimiento == 2 || movimiento == 5 || movimiento == 8)
			movimiento = 0;
		else if (movimiento == 3 || movimiento == 4 || movimiento == 9)
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
	sprite_pegando_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - 20.f), float(tileMapDispl.y + posPlayer.y)));
	sprite_saltar_derecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_saltar_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_patada_derecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_patada_izquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - 20.f), float(tileMapDispl.y + posPlayer.y)));*/

	sprite->update(deltaTime);
	sprite_caminando->update(deltaTime);
	sprite_standLeft->update(deltaTime);
	sprite_caminando_izq->update(deltaTime);
	sprite_pegando_derecha->update(deltaTime);
	sprite_pegando_izquierda->update(deltaTime);
	sprite_saltar_derecha->update(deltaTime);
	sprite_saltar_izquierda->update(deltaTime);
	sprite_patada_derecha->update(deltaTime);
	sprite_patada_izquierda->update(deltaTime);
	//sprite_correr->update(deltaTime);

	if (Game::instance().getKey('x') && (movimiento == 1 || movimiento == 3 || movimiento == 4)) {
		movimiento = 4;
	}

	else if (Game::instance().getKey('x') && (movimiento == 0 || movimiento == 2 || movimiento == 5)) {
		movimiento = 5;
	}

	else if (Game::instance().getKey('c') && (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 9)) {
		if (movimiento != 9)sprite_patada_derecha->changeAnimation(0);
		movimiento = 9;
	}

	else if (Game::instance().getKey('c') && (movimiento == 0 || movimiento == 2 || movimiento == 5 || movimiento == 8)) {
		if (movimiento != 8)sprite_patada_izquierda->changeAnimation(0);
		movimiento = 8;
	}


	else if (Game::instance().getKey('<') && (Game::instance().getSpecialKey(GLUT_KEY_LEFT) || (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)))) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			if (!bJumping) movimiento = 10;
			//if (sprite_correr->animation() == 0) sprite_correr->changeAnimation(1);
			if (posPlayer.x > 60) posPlayer.x -= 4;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			if (!bJumping) movimiento = 10;
			//if (sprite_correr->animation() == 1) sprite_correr->changeAnimation(0);
			if (posPlayer.x < 540) posPlayer.x += 4;
		}
	}


	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (!bJumping) movimiento = 2;
		if (posPlayer.x > 60) posPlayer.x -= 2.f;
		/*if (map->collisionMoveLeft(posPlayer, glm::ivec2(38.625, 61)))
		{
		if (!bJumping) movimiento = 0;
		posPlayer.x += 2;
		}*/
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (!bJumping) movimiento = 3;
		if (posPlayer.x < 540) posPlayer.x += 2;
		/*if (map->collisionMoveRight(posPlayer, glm::ivec2(38.625, 61)))
		{
		if (!bJumping) movimiento = 1;

		posPlayer.x -= 2;
		}*/
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getKey('c') && !Game::instance().getKey('x') && posPlayer.y > 165)
	{
		if (!bJumping && movimiento == 3 || movimiento == 1) movimiento = 3;
		if (!bJumping && movimiento == 2 || movimiento == 0) movimiento = 2;
		posPlayer.y -= 2;
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !Game::instance().getKey('c') && !Game::instance().getKey('x') && posPlayer.y < 380)
	{
		if (!bJumping && movimiento == 3 || movimiento == 1) movimiento = 3;
		if (!bJumping && movimiento == 2 || movimiento == 0) movimiento = 2;
		posPlayer.y += 2;
	}


	else if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !Game::instance().getKey('x') && !Game::instance().getKey('c'))
	{
		if (movimiento == 2 || movimiento == 5 || movimiento == 8 || movimiento == 10)
			movimiento = 0;
		else if (movimiento == 3 || movimiento == 4 || movimiento == 9 || movimiento == 10)
			movimiento = 1;
	}

	if (bJumping)
	{
		if (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 7 || movimiento == 10)
			movimiento = 7;
		else movimiento = 6;

		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
			if (movimiento == 6) movimiento = 0;
			else movimiento = 1;

		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				//bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(38.625, 61), &posPlayer.y);
				if (!bJumping) {
					if (movimiento == 6) movimiento = 0;
					else movimiento = 1;
				}
			}
		}
	}
	else
	{
		if (Game::instance().getKey('z'))
		{
			bJumping = true;
			sprite_saltar_derecha->changeAnimation(0);
			sprite_saltar_izquierda->changeAnimation(0);
			jumpAngle = 0;
			startY = posPlayer.y;
		}
		/*posPlayer.y += FALL_STEP;
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

		}*/
	}
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_saltar_derecha->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_saltar_izquierda->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_patada_derecha->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_patada_izquierda->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	//sprite_correr->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	}

void Kim::render()
{
	if (movimiento == 0) sprite_standLeft->render();
	else if (movimiento == 1) sprite->render();
	else if (movimiento == 2) sprite_caminando_izq->render();
	else if (movimiento == 3) sprite_caminando->render();
	else if (movimiento == 4) sprite_pegando_derecha->render();
	else if (movimiento == 5) sprite_pegando_izquierda->render();
	else if (movimiento == 6) sprite_saltar_izquierda->render();
	else if (movimiento == 7) sprite_saltar_derecha->render();
	else if (movimiento == 8) sprite_patada_izquierda->render();
	else if (movimiento == 9) sprite_patada_derecha->render();
}

void Kim::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Kim::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::vec2 Kim::getPosition()
{
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
}

bool Kim::isWalking() {
	if (movimiento == 2 || movimiento == 3 || movimiento == 6 || movimiento == 7) return true;
	else return false;
}


bool Kim::isRunning() {
	if (movimiento == 10 || movimiento == 6 || movimiento == 7) return true;
	else return false;
}

bool Kim::isKicking_left() {
	if (movimiento == 8) return true;
	else return false;
}
bool Kim::isKicking_right() {
	if (movimiento == 9) return true;
	else return false;
}
bool Kim::isPunching_left() {
	if (movimiento == 5) return true;
	else return false;
}
bool Kim::isPunching_right() {
	if (movimiento == 4) return true;
	else return false;
}

void Kim::recibirPuñetazoIzquierda() {

}

void Kim::recibirPuñetazoDerecha() {

}