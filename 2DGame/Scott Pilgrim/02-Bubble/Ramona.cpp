#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ramona.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

void Ramona::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lev)
{
	level = lev;
	posLevel = 50;
	derecha = true;
	mapShader = shaderProgram;
	movimiento = 0;
	bJumping = false;
	spritesheet.loadFromFile("images/Ramona/RamonaQuieta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.1666667, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.1666667f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.3333333f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.6666667f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.8333333f, 0.f));

	spritesheet_standLeft.loadFromFile("images/Ramona/RamonaQuietaIz.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_standLeft = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.1666667, 1), &spritesheet_standLeft, &shaderProgram);
	sprite_standLeft->setNumberAnimations(4);

	sprite_standLeft->setAnimationSpeed(STAND_LEFT, 8);
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.8333333f, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.6666667f, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.3333333f, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.1666667f, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));


	spritesheet_caminando.loadFromFile("images/Ramona/RamonaCaminar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.1666666667, 1), &spritesheet_caminando, &shaderProgram);
	sprite_caminando->setNumberAnimations(4);


	sprite_caminando->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666666667, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333333333, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.6777777777, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.83333333333, 0.f));

	spritesheet_caminando_izq.loadFromFile("images/Ramona/RamonaCaminarIz.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando_izq = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.1666666667, 1), &spritesheet_caminando_izq, &shaderProgram);
	sprite_caminando_izq->setNumberAnimations(4);


	sprite_caminando_izq->setAnimationSpeed(MOVE_LEFT, 8);
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.833333333, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.6777777777, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.3333333333, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.1666666667, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	spritesheet_pegando_derecha.loadFromFile("images/Ramona/RamonaGuantazo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_pegando_derecha = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.11111111, 1), &spritesheet_pegando_derecha, &shaderProgram);
	sprite_pegando_derecha->setNumberAnimations(1);

	sprite_pegando_derecha->setAnimationSpeed(0, 8);
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.11111111f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.22222222f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.33333333f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.44444444f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.55555555f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.66666666f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.77777777f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.88888888f, 0.f));

	spritesheet_pegando_izquierda.loadFromFile("images/Ramona/RamonaGuantazoIz.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_pegando_izquierda = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.11111111, 1), &spritesheet_pegando_izquierda, &shaderProgram);
	sprite_pegando_izquierda->setNumberAnimations(1);

	sprite_pegando_izquierda->setAnimationSpeed(0, 8);
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.88888888f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.77777777f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.66666666f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.55555555f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.44444444f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.33333333f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.22222222f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.11111111f, 0.f));
	sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.f, 0.f));

	spritesheet_saltar_derecha.loadFromFile("images/Ramona/RamonaSaltando.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_saltar_derecha = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.11111111, 1), &spritesheet_saltar_derecha, &shaderProgram);
	sprite_saltar_derecha->setNumberAnimations(1);

	sprite_saltar_derecha->setAnimationSpeed(0, 8);
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.11111111f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.22222222f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.33333333f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.44444444f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.55555555f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.66666666f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.77777777f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.88888888f, 0.f));

	spritesheet_saltar_izquierda.loadFromFile("images/Ramona/RamonaSaltandoIz.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_saltar_izquierda = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.11111111, 1), &spritesheet_saltar_izquierda, &shaderProgram);
	sprite_saltar_izquierda->setNumberAnimations(1);

	sprite_saltar_izquierda->setAnimationSpeed(0, 8);
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.88888888f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.77777777f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.66666666f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.55555555f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.44444444f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.33333333f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.22222222f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.11111111f, 0.f));
	sprite_saltar_izquierda->addKeyframe(0, glm::vec2(0.f, 0.f));

	spritesheet_rayo_derecha.loadFromFile("images/Ramona/RamonaRayo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_rayo_derecha = Sprite::createSprite(glm::ivec2(100, 100), glm::vec2(0.11111111, 1), &spritesheet_rayo_derecha, &shaderProgram);
	sprite_rayo_derecha->setNumberAnimations(1);

	sprite_rayo_derecha->setAnimationSpeed(0, 8);
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.11111111f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.22222222f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.33333333f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.44444444f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.55555555f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.66666666f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.77777777f, 0.f));
	sprite_rayo_derecha->addKeyframe(0, glm::vec2(0.88888888f, 0.f));

	spritesheet_rayo_izquierda.loadFromFile("images/Ramona/RamonaRayoIz.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_rayo_izquierda = Sprite::createSprite(glm::ivec2(100, 100), glm::vec2(0.11111111, 1), &spritesheet_rayo_izquierda, &shaderProgram);
	sprite_rayo_izquierda->setNumberAnimations(1);

	sprite_rayo_izquierda->setAnimationSpeed(0, 8);
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.88888888f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.77777777f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.66666666f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.55555555f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.44444444f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.33333333f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.22222222f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.11111111f, 0.f));
	sprite_rayo_izquierda->addKeyframe(0, glm::vec2(0.f, 0.f));

	spritesheet_correr.loadFromFile("images/Ramona/RamonaCorriendo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_correr = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.125, 1), &spritesheet_correr, &shaderProgram);
	sprite_correr->setNumberAnimations(1);

	sprite_correr->setAnimationSpeed(0, 10);
	sprite_correr->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.125, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.25, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.375, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.5, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.625f, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.875f, 0.f));

	spritesheet_correr_iz.loadFromFile("images/Ramona/RamonaCorriendoIz.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_correr_iz = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.125, 1), &spritesheet_correr_iz, &shaderProgram);
	sprite_correr_iz->setNumberAnimations(1);

	sprite_correr_iz->setAnimationSpeed(0, 10);
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.875f, 0.f));
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.625f, 0.f));
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.5, 0.f));
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.375, 0.f));
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.25, 0.f));
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.125, 0.f));
	sprite_correr_iz->addKeyframe(0, glm::vec2(0.f, 0.f));

	spritesheet_martillo.loadFromFile("images/Ramona/RamonaTriangulo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_martillo = Sprite::createSprite(glm::ivec2(100, 120), glm::vec2(0.125, 1), &spritesheet_martillo, &shaderProgram);
	sprite_martillo->setNumberAnimations(1);

	sprite_martillo->setAnimationSpeed(0, 10);
	sprite_martillo->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_martillo->addKeyframe(0, glm::vec2(0.125, 0.f));
	sprite_martillo->addKeyframe(0, glm::vec2(0.25, 0.f));
	sprite_martillo->addKeyframe(0, glm::vec2(0.375, 0.f));
	sprite_martillo->addKeyframe(0, glm::vec2(0.5, 0.f));
	sprite_martillo->addKeyframe(0, glm::vec2(0.625f, 0.f));
	sprite_martillo->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite_martillo->addKeyframe(0, glm::vec2(0.875f, 0.f));

	spritesheet_martillo_izq.loadFromFile("images/Ramona/RamonaTrianguloIz.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_martillo_iz = Sprite::createSprite(glm::ivec2(100, 120), glm::vec2(0.125, 1), &spritesheet_martillo_izq, &shaderProgram);
	sprite_martillo_iz->setNumberAnimations(1);

	sprite_martillo_iz->setAnimationSpeed(0, 10);
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.875f, 0.f));
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.625f, 0.f));
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.5, 0.f));
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.375, 0.f));
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.25, 0.f));
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.125, 0.f));
	sprite_martillo_iz->addKeyframe(0, glm::vec2(0.f, 0.f));




	sprite->changeAnimation(STAND_RIGHT);
	sprite_standLeft->changeAnimation(STAND_LEFT);
	sprite_caminando->changeAnimation(MOVE_RIGHT);
	sprite_caminando_izq->changeAnimation(MOVE_LEFT);
	sprite_pegando_derecha->changeAnimation(0);
	sprite_pegando_izquierda->changeAnimation(0);
	sprite_saltar_derecha->changeAnimation(0);
	sprite_saltar_izquierda->changeAnimation(0);
	sprite_rayo_derecha->changeAnimation(0);
	sprite_correr->changeAnimation(0);
	//tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
}

void Ramona::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite_caminando->update(deltaTime);
	sprite_standLeft->update(deltaTime);
	sprite_caminando_izq->update(deltaTime);
	sprite_pegando_derecha->update(deltaTime);
	sprite_pegando_izquierda->update(deltaTime);
	sprite_saltar_derecha->update(deltaTime);
	sprite_saltar_izquierda->update(deltaTime);
	sprite_rayo_derecha->update(deltaTime);
	sprite_rayo_izquierda->update(deltaTime);
	sprite_correr->update(deltaTime);
	sprite_correr_iz->update(deltaTime);
	sprite_martillo->update(deltaTime);
	sprite_martillo_iz->update(deltaTime);

	if (Game::instance().getKey('x') && (movimiento == 1 || movimiento == 3 || movimiento == 4)) {
		if (movimiento != 4)sprite_pegando_derecha->changeAnimation(0);
		movimiento = 4;
	}

	else if (Game::instance().getKey('x') && (movimiento == 0 || movimiento == 2 || movimiento == 5)) {
		if (movimiento != 5)sprite_pegando_izquierda->changeAnimation(0);
		movimiento = 5;
	}

	else if (Game::instance().getKey('c') && (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 9)) {
		if (movimiento != 9)sprite_rayo_derecha->changeAnimation(0);
		movimiento = 9;
	}

	else if (Game::instance().getKey('c') && (movimiento == 0 || movimiento == 2 || movimiento == 5 || movimiento == 8)) {
		if (movimiento != 8)sprite_rayo_izquierda->changeAnimation(0);
		movimiento = 8;
	}

	else if (Game::instance().getKey('v') && (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 11)) {
		if (movimiento != 11) sprite_martillo->changeAnimation(0);
		movimiento = 11;
	}

	else if (Game::instance().getKey('v') && (movimiento == 0 || movimiento == 2 || movimiento == 5 || movimiento == 12)) {
		if (movimiento != 12)sprite_martillo_iz->changeAnimation(0);
		movimiento = 12;
	}


	else if (Game::instance().getKey('<') && (Game::instance().getSpecialKey(GLUT_KEY_LEFT) || (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)))) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			if (!bJumping) movimiento = 10;
			if (derecha) sprite_correr_iz->changeAnimation(0);
			if (posRamona.x > 60) {
				posRamona.x -= 4.f;
				posLevel -= 4.f;
			}
			derecha = false;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			if (!bJumping) movimiento = 10;
			if (!derecha) sprite_correr->changeAnimation(0);
			if (posLevel < 5000) {
				if (posRamona.x < 540) {
					posRamona.x += 4.f;
				}
				posLevel += 4.f;
			}
			derecha = true;
		}
	}


	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (!bJumping) movimiento = 2;
		if (posRamona.x > 60) {
			posRamona.x -= 2.f;
			posLevel -= 2.f;
		}
		/*if (map->collisionMoveLeft(posPlayer, glm::ivec2(38.625, 61)))
		{
			if (!bJumping) movimiento = 0;
			posPlayer.x += 2;
		}*/
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (!bJumping) movimiento = 3;
		if (posLevel < 5000) {
			if (posRamona.x < 540) {
				posRamona.x += 2.f;
			}
			posLevel += 2.f;
		}
		/*if (map->collisionMoveRight(posPlayer, glm::ivec2(38.625, 61)))
		{
			if (!bJumping) movimiento = 1;

			posPlayer.x -= 2;
		}*/
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getKey('c') && !Game::instance().getKey('x') && posRamona.y > 165)
	{
		if ((level == 1 && posRamona.y > 165) || (level == 2 && posRamona.y > 210)) {
			if (!bJumping && movimiento == 3 || movimiento == 1) movimiento = 3;
			if (!bJumping && movimiento == 2 || movimiento == 0) movimiento = 2;
			posRamona.y -= 2;
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !Game::instance().getKey('c') && !Game::instance().getKey('x') && posRamona.y < 380)
	{
		if (!bJumping && movimiento == 3 || movimiento == 1) movimiento = 3;
		if (!bJumping && movimiento == 2 || movimiento == 0) movimiento = 2;
		posRamona.y += 2;
	}


	else if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !Game::instance().getKey('x') && !Game::instance().getKey('c') && !Game::instance().getKey('v'))
	{
		if (movimiento == 2 || movimiento == 5 || movimiento == 8 || movimiento == 10 && sprite_correr->animation() == 1 || movimiento == 12)
			movimiento = 0;
		else if (movimiento == 3 || movimiento == 4 || movimiento == 9 || movimiento == 10 && sprite_correr->animation() == 0 || movimiento == 11)
			movimiento = 1;
	}

	if (bJumping)
	{
		if (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 7 || movimiento == 10 && sprite_correr->animation() == 0)
			movimiento = 7;
		else movimiento = 6;

		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posRamona.y = startY;
			if (movimiento == 6) movimiento = 0;
			else movimiento = 1;

		}
		else
		{
			posRamona.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
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
			startY = posRamona.y;
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
	sprite->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_caminando->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_standLeft->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float(posRamona.x - 20), float(posRamona.y)));
	sprite_saltar_derecha->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_saltar_izquierda->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_rayo_derecha->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
	sprite_rayo_izquierda->setPosition(glm::vec2(float(posRamona.x - 20), float(posRamona.y)));
	sprite_correr->setPosition(glm::vec2(float(posRamona.x - 20), float(posRamona.y)));
	sprite_correr_iz->setPosition(glm::vec2(float(posRamona.x - 20), float(posRamona.y)));
	sprite_martillo->setPosition(glm::vec2(float(posRamona.x - 20), float(posRamona.y)));
	sprite_martillo_iz->setPosition(glm::vec2(float(posRamona.x - 20), float(posRamona.y)));
}

void Ramona::render()
{
	switch (movimiento)
	{
	case 0:
		sprite_standLeft->render();
		break;
	case 1:
		sprite->render();
		break;
	case 2:
		sprite_caminando_izq->render();
		break;
	case 3:
		sprite_caminando->render();
		break;
	case 4:
		sprite_pegando_derecha->render();
		break;
	case 5:
		sprite_pegando_izquierda->render();
		break;
	case 6:
		sprite_saltar_izquierda->render();
		break;
	case 7:
		sprite_saltar_derecha->render();
		break;
	case 8:
		sprite_rayo_izquierda->render();
		break;
	case 9:
		sprite_rayo_derecha->render();
		break;
	case 10:
		if (derecha) sprite_correr->render();
		else sprite_correr_iz->render();
		break;
	case 11:
		sprite_martillo->render();
		break;
	case 12:
		sprite_martillo_iz->render();
		break;
	}
}

void Ramona::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
}

void Ramona::setPosition(const glm::vec2 &pos)
{
	posRamona = pos;
	sprite->setPosition(glm::vec2(float(posRamona.x), float(posRamona.y)));
}

glm::vec2 Ramona::getPosition()
{
	return glm::vec2(float(posRamona.x), float(posRamona.y));
}

float Ramona::getPosLevel() {
	return posLevel;
}

bool Ramona::isWalking() {
	if (movimiento == 2 || movimiento == 3 || movimiento == 6 || movimiento == 7) return true;
	else return false;
}


bool Ramona::isRunning() {
	if (movimiento == 10 || movimiento == 6 || movimiento == 7) return true;
	else return false;
}

bool Ramona::isKicking_left() {
	if (movimiento == 8) return true;
	else if (movimiento == 12) return true;
	else return false;
}
bool Ramona::isKicking_right() {
	if (movimiento == 9) return true;
	else if (movimiento == 11) return true;
	else return false;
}
bool Ramona::isPunching_left() {
	if (movimiento == 5) return true;
	else return false;
}
bool Ramona::isPunching_right() {
	if (movimiento == 4) return true;
	else return false;
}




