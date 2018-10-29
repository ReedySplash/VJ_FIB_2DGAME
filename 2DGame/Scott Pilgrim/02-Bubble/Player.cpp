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


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lev)
{	
	level = lev;
	vida = 100;
	posLevel = 75;
	mapShader = shaderProgram;
	movimiento = 1;
	bJumping = false;
	spritesheet.loadFromFile("images/Scott/Scott quieto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.125, 1), &spritesheet, &shaderProgram);
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

	spritesheet_standLeft.loadFromFile("images/Scott/Scott quieto left.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_standLeft = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.125, 1), &spritesheet_standLeft, &shaderProgram);
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


	spritesheet_caminando.loadFromFile("images/Scott/0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.1666666667, 1), &spritesheet_caminando, &shaderProgram);
	sprite_caminando->setNumberAnimations(4);


		sprite_caminando->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666666667, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333333333, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.6777777777, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.83333333333, 0.f));

	spritesheet_caminando_izq.loadFromFile("images/Scott/0_izq.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_caminando_izq = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.1666666667, 1), &spritesheet_caminando_izq, &shaderProgram);
		sprite_caminando_izq->setNumberAnimations(4);


		sprite_caminando_izq->setAnimationSpeed(MOVE_LEFT, 8);
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.833333333, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.6777777777, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.3333333333, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.1666666667, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	spritesheet_pegando_derecha.loadFromFile("images/Scott/atacar_puño_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_pegando_derecha = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.0588235294, 1), &spritesheet_pegando_derecha, &shaderProgram);
			sprite_pegando_derecha->setNumberAnimations(1);

			sprite_pegando_derecha->setAnimationSpeed(0, 11);
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

	spritesheet_pegando_izquierda.loadFromFile("images/Scott/atacar_puño_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_pegando_izquierda = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.0588235294, 1), &spritesheet_pegando_izquierda, &shaderProgram);
			sprite_pegando_izquierda->setNumberAnimations(1);

			sprite_pegando_izquierda->setAnimationSpeed(0, 11);
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.117647059, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*3.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*4.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*5.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*6.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*7.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*8.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*9.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*10.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*11.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*12.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*13.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*14.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*15.f, 0.f));
			sprite_pegando_izquierda->addKeyframe(0, glm::vec2(0.0588235294f*16.f, 0.f));

	spritesheet_saltar_derecha.loadFromFile("images/Scott/saltar_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_saltar_derecha = Sprite::createSprite(glm::ivec2(47, 100), glm::vec2(0.0769230769, 1), &spritesheet_saltar_derecha, &shaderProgram);
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

	spritesheet_saltar_izquierda.loadFromFile("images/Scott/saltar_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_saltar_izquierda = Sprite::createSprite(glm::ivec2(47, 100), glm::vec2(0.0769230769, 1), &spritesheet_saltar_izquierda, &shaderProgram);
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
			sprite_saltar_izquierda->addKeyframe(1, glm::vec2(0.0769230769 * 2, 0.f));
			sprite_saltar_izquierda->addKeyframe(1, glm::vec2(0.0769230769 * 1, 0.f));

	spritesheet_patada_derecha.loadFromFile("images/Scott/patada_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_patada_derecha = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.125, 1), &spritesheet_patada_derecha, &shaderProgram);
			sprite_patada_derecha->setNumberAnimations(1);

			sprite_patada_derecha->setAnimationSpeed(0, 10);
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.125, 0.f));
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.25, 0.f));
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.375, 0.f));
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.5, 0.f));
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.625f, 0.f));
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.75f, 0.f));
			sprite_patada_derecha->addKeyframe(0, glm::vec2(0.875f, 0.f));

	spritesheet_patada_izquierda.loadFromFile("images/Scott/patada_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_patada_izquierda = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.125, 1), &spritesheet_patada_izquierda, &shaderProgram);
			sprite_patada_izquierda->setNumberAnimations(1);

			sprite_patada_izquierda->setAnimationSpeed(0, 10);
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.875, 0.f));
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.75, 0.f));
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.625, 0.f));
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.5, 0.f));
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.375, 0.f));
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.25, 0.f));
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.125, 0.f));
			sprite_patada_izquierda->addKeyframe(0, glm::vec2(0, 0.f));

	spritesheet_correr.loadFromFile("images/Scott/scott_correr.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite_correr = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.0625, 1), &spritesheet_correr, &shaderProgram);
			sprite_correr->setNumberAnimations(2);

			sprite_correr->setAnimationSpeed(0, 10);
			sprite_correr->addKeyframe(0, glm::vec2(0, 0.f));
			sprite_correr->addKeyframe(0, glm::vec2(0.0625, 0.f));
			sprite_correr->addKeyframe(0, glm::vec2(0.0625*2, 0.f));
			sprite_correr->addKeyframe(0, glm::vec2(0.0625*3, 0.f));
			sprite_correr->addKeyframe(0, glm::vec2(0.0625*4, 0.f));
			sprite_correr->addKeyframe(0, glm::vec2(0.0625*5, 0.f));
			sprite_correr->addKeyframe(0, glm::vec2(0.0625*6, 0.f));
			sprite_correr->addKeyframe(0, glm::vec2(0.0625*7, 0.f));

			sprite_correr->setAnimationSpeed(1, 10);
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 8, 0.f));
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 9, 0.f));
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 10, 0.f));
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 11, 0.f));
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 12, 0.f));
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 13, 0.f));
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 14, 0.f));
			sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 15, 0.f));

	spritesheet_puñetazo_arriba.loadFromFile("images/Scott/scott_puñetazo_arriba_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	puñetazo_arriba = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.125, 1), &spritesheet_puñetazo_arriba, &shaderProgram);
	puñetazo_arriba->setNumberAnimations(1);

		puñetazo_arriba->setAnimationSpeed(0, 12);
		puñetazo_arriba->addKeyframe(0, glm::vec2(0, 0.f));
		puñetazo_arriba->addKeyframe(0, glm::vec2(0.125, 0.f));
		puñetazo_arriba->addKeyframe(0, glm::vec2(0.125 * 2, 0.f));
		puñetazo_arriba->addKeyframe(0, glm::vec2(0.125 * 3, 0.f));
		puñetazo_arriba->addKeyframe(0, glm::vec2(0.125 * 4, 0.f));
		puñetazo_arriba->addKeyframe(0, glm::vec2(0.125 * 5, 0.f));
		puñetazo_arriba->addKeyframe(0, glm::vec2(0.125 * 6, 0.f));
		puñetazo_arriba->addKeyframe(0, glm::vec2(0.125 * 7, 0.f));

	spritesheet_puñetazo_arriba_izq.loadFromFile("images/Scott/scott_puñetazo_arriba_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
	puñetazo_arriba_izq = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.125, 1), &spritesheet_puñetazo_arriba_izq, &shaderProgram);
	puñetazo_arriba_izq->setNumberAnimations(1);

		puñetazo_arriba_izq->setAnimationSpeed(0, 12);
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.125 * 7, 0.f));
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.125 * 6, 0.f));
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.125 * 5, 0.f));
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.125 * 4, 0.f));
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.125 * 3, 0.f));
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.125 * 2, 0.f));
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.125, 0.f));
		puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0, 0.f));

	spritesheet_recibir_daño.loadFromFile("images/Scott/recibir_daño.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_recibir = Sprite::createSprite(glm::ivec2(80, 120), glm::vec2(0.0357142857, 1), &spritesheet_recibir_daño, &shaderProgram);
		sprite_recibir->setNumberAnimations(5);

		sprite_recibir->setAnimationSpeed(0, 4);
		sprite_recibir->addKeyframe(0, glm::vec2(0.0357142857 * 0, 0.f));
		sprite_recibir->addKeyframe(0, glm::vec2(0.0357142857, 0.f));

		sprite_recibir->setAnimationSpeed(1, 6);
		sprite_recibir->addKeyframe(1, glm::vec2(0.0357142857 * 2, 0.f));
		sprite_recibir->addKeyframe(1, glm::vec2(0.0357142857 * 3, 0.f));
		sprite_recibir->addKeyframe(1, glm::vec2(0.0357142857 * 4, 0.f));
		sprite_recibir->addKeyframe(1, glm::vec2(0.0357142857 * 5, 0.f));
		sprite_recibir->addKeyframe(1, glm::vec2(0.0357142857 * 6, 0.f));
		
		sprite_recibir->setAnimationSpeed(2, 10);
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 7, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 8, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 9, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 10, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 11, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 12, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 13, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 14, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 15, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 16, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 17, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 18, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 19, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 20, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 21, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 22, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 23, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 24, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 25, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 26, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 27, 0.f));

		sprite_recibir->setAnimationSpeed(3, 10);
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 7, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 8, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 9, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 10, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 11, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 12, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 13, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 14, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 15, 0.f));
		sprite_recibir->addKeyframe(3, glm::vec2(0.0357142857 * 16, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 17, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 18, 0.f));
		sprite_recibir->addKeyframe(2, glm::vec2(0.0357142857 * 19, 0.f));

		

		sprite_recibir->setAnimationSpeed(4, 10);
		sprite_recibir->addKeyframe(4, glm::vec2(0.0357142857 * 19, 0.f));

	spritesheet_recibir_daño_izq.loadFromFile("images/Scott/recibir_daño_izq.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_recibir_izq = Sprite::createSprite(glm::ivec2(80, 130), glm::vec2(0.0357142857, 1), &spritesheet_recibir_daño_izq, &shaderProgram);
		sprite_recibir_izq->setNumberAnimations(5);

		sprite_recibir_izq->setAnimationSpeed(0, 4);
		sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0357142857 * 27, 0.f));
		sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0357142857 * 26, 0.f));

		sprite_recibir_izq->setAnimationSpeed(1, 6);
		sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0357142857 * 25, 0.f));
		sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0357142857 * 24, 0.f));
		sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0357142857 * 23, 0.f));
		sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0357142857 * 22, 0.f));
		sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0357142857 * 21, 0.f));

		sprite_recibir_izq->setAnimationSpeed(2, 10);
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 20, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 19, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 18, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 17, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 16, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 15, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 14, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 13, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 12, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 11, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 10, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 9, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 8, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 7, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 6, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 5, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 4, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 3, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 2, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 1, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 0, 0.f));

		sprite_recibir_izq->setAnimationSpeed(3, 10);
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 20, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 19, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 18, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 17, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 16, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 15, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 14, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 13, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 12, 0.f));
		sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0357142857 * 11, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 10, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 9, 0.f));
		sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0357142857 * 8, 0.f));
		

		sprite_recibir_izq->setAnimationSpeed(4, 10);
		sprite_recibir_izq->addKeyframe(4, glm::vec2(0.0357142857 *8, 0.f));


			
	sprite->changeAnimation(STAND_RIGHT);
	sprite_standLeft->changeAnimation(STAND_LEFT);
	sprite_caminando->changeAnimation(MOVE_RIGHT);
	sprite_caminando_izq->changeAnimation(MOVE_LEFT);
	sprite_correr->changeAnimation(0);
	//tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
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
	sprite_patada_derecha->update(deltaTime);
	sprite_patada_izquierda->update(deltaTime);
	sprite_correr->update(deltaTime);
	puñetazo_arriba->update(deltaTime);
	puñetazo_arriba_izq->update(deltaTime);
	sprite_recibir_izq->update(deltaTime);
	sprite_recibir->update(deltaTime);

	if (vida <= 0) {
		if (movimiento == 13 && sprite_recibir_izq->animation() != 3 && sprite_recibir_izq->animation() != 4) sprite_recibir_izq->changeAnimation(3);
		else if (movimiento == 14 && sprite_recibir->animation() != 3 && sprite_recibir->animation() != 4) sprite_recibir->changeAnimation(3);
		else if (!sprite_recibir_izq->isFinalized() && sprite_recibir_izq->animation() != 4) ++posPlayer.x;
		else if (!sprite_recibir->isFinalized() && sprite_recibir->animation() != 4) --posPlayer.x;
		if (sprite_recibir->animation() != 4 && sprite_recibir_izq->animation() != 4) posPlayer.y += 0.6;
		if (movimiento == 13 && sprite_recibir_izq->isFinalized()) {
			//if (sprite_recibir_izq->animation() != 4) posPlayer.y -= 15.4f;
			sprite_recibir_izq->changeAnimation(4); 
		}
		else if (movimiento == 14 && sprite_recibir->isFinalized()) {
			//if (sprite_recibir->animation() != 4) posPlayer.y -= 15.4f;
			sprite_recibir->changeAnimation(4);
		}
	}

	else {

		if (movimiento == 13 || movimiento == 14 && (sprite_recibir->animation() == 2 || sprite_recibir_izq->animation() == 2)) {
			if (sprite_recibir->animation() == 2 || sprite_recibir_izq->animation() == 2) recuperando += deltaTime;
			if (sprite_recibir->animation() == 2 && movimiento == 14 && recuperando < 1500) posPlayer.x -= 1.5f;
			else if (sprite_recibir_izq->animation() == 2 && movimiento == 13 && recuperando < 1500) posPlayer.x += 1.5f;
			if (recuperando < 1300) posPlayer.y += 0.25;
			else if (recuperando > 2300) {
				if (movimiento == 13) movimiento = 0;
				else movimiento = 1;
				recuperando = 0;
				posPlayer.y -= 18.4f;
			}
		}


		if (sprite_pegando_derecha->isFinalized() && sprite_pegando_izquierda->isFinalized() && sprite_patada_derecha->isFinalized() && sprite_patada_izquierda->isFinalized() && puñetazo_arriba->isFinalized() && puñetazo_arriba_izq->isFinalized() && movimiento != 13 && movimiento != 14) {
			if (Game::instance().getKey('x') && (movimiento == 1 || movimiento == 3 || movimiento == 4)) {
				if (movimiento != 4) {
					sprite_pegando_derecha->changeAnimation(0);
				}
				movimiento = 4;
			}

			else if (Game::instance().getKey('x') && (movimiento == 0 || movimiento == 2 || movimiento == 5)) {
				if (movimiento != 5) {
					sprite_pegando_izquierda->changeAnimation(0);
				}
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

			else if (Game::instance().getKey('v') && (movimiento == 1 || movimiento == 3 || movimiento == 4 || movimiento == 11)) {
				if (movimiento != 11) puñetazo_arriba->changeAnimation(0);
				movimiento = 11;
			}

			else if (Game::instance().getKey('v') && (movimiento == 0 || movimiento == 2 || movimiento == 5 || movimiento == 12)) {
				if (movimiento != 12)puñetazo_arriba_izq->changeAnimation(0);
				movimiento = 12;
			}


			else if (Game::instance().getKey('<') && (Game::instance().getSpecialKey(GLUT_KEY_LEFT) || (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)))) {
				if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
					if (!bJumping) movimiento = 10;
					if (sprite_correr->animation() == 0) sprite_correr->changeAnimation(1);
					if (posPlayer.x > 200 && posLevel >= 210) {
						posPlayer.x -= 4.f;
						posLevel -= 4.f;
					}
					else if (posPlayer.x > 0 && posLevel < 210) {
						posPlayer.x -= 4.f;
						posLevel -= 4.f;
					}
					else if (posPlayer.x > 0 && posLevel > 2300) {
						posPlayer.x -= 4.f;
						posLevel -= 4.f;
					}
					else posLevel -= 4.f;
					if (posPlayer.x <= 0) posLevel += 4.f;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
					if (!bJumping) movimiento = 10;
					if (sprite_correr->animation() == 1) sprite_correr->changeAnimation(0);
					if (posPlayer.x < 380 && posLevel >= 0) {
						posPlayer.x += 4.f;
						posLevel += 4.f;
					}
					else if (posPlayer.x < 580 && posLevel > 2740) {
						posPlayer.x += 4.f;
						posLevel += 4.f;
					}
					else posLevel += 4.f;
					if (posPlayer.x >= 580) posLevel -= 4.f;
				}
			}


			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				if (!bJumping) movimiento = 2;
				if (posPlayer.x > 200 && posLevel >= 210) {
					posPlayer.x -= 2.f;
					posLevel -= 2.f;
				}
				else if (posPlayer.x > 0 && posLevel < 210) {
					posPlayer.x -= 2.f;
					posLevel -= 2.f;
				}
				else if (posPlayer.x > 0 && posLevel > 2300) {
					posPlayer.x -= 2.f;
					posLevel -= 2.f;
				}
				else posLevel -= 2.f;
				if (posPlayer.x <= 0) posLevel += 2.f;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (!bJumping) movimiento = 3;
				if (posPlayer.x < 380 && posLevel >= 0 ) {
					posPlayer.x += 2.f;
					posLevel += 2.f;
				}
				else if (posPlayer.x < 580 && posLevel > 2740) {
					posPlayer.x += 2.f;
					posLevel += 2.f;
				}
				else posLevel += 2.f;
				if (posPlayer.x >= 580) posLevel -= 2.f;
			}

			if (Game::instance().getSpecialKey(GLUT_KEY_UP) && posPlayer.y > 165)
			{
				if ((level == 1 && posPlayer.y > 165) || (level == 2 && posPlayer.y > 210)) {
					if (!bJumping && movimiento == 3 || movimiento == 1) movimiento = 3;
					if (!bJumping && movimiento == 2 || movimiento == 0) movimiento = 2;
					posPlayer.y -= 2;
				}
			}

			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && posPlayer.y < 380)
			{
				if (!bJumping && movimiento == 3 || movimiento == 1) movimiento = 3;
				if (!bJumping && movimiento == 2 || movimiento == 0) movimiento = 2;
				posPlayer.y += 2;
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
			}
		}
	}

	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float( posPlayer.x), float( posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float( posPlayer.x), float(  posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(  posPlayer.x-5), float(  posPlayer.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float( posPlayer.x), float(  posPlayer.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float( posPlayer.x-20), float(  posPlayer.y)));
	sprite_saltar_derecha->setPosition(glm::vec2(float(  posPlayer.x), float(  posPlayer.y)));
	sprite_saltar_izquierda->setPosition(glm::vec2(float( posPlayer.x ), float( posPlayer.y)));
	sprite_patada_derecha->setPosition(glm::vec2(float(  posPlayer.x), float(  posPlayer.y)));
	sprite_patada_izquierda->setPosition(glm::vec2(float(  posPlayer.x-20), float(  posPlayer.y)));
	sprite_correr->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	puñetazo_arriba->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	puñetazo_arriba_izq->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_recibir->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y - 15)));
	sprite_recibir_izq->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y - 15)));
}

void Player::render()
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
			sprite_patada_izquierda->render();
			break;
		case 9:
			sprite_patada_derecha->render();
			break;
		case 10:
			sprite_correr->render();
			break;
		case 11:
			puñetazo_arriba->render();
			break;
		case 12:
			puñetazo_arriba_izq->render();
			break;
		case 13:
			sprite_recibir_izq->render();
			break;
		case 14:
			sprite_recibir->render();
			break;
	}
}

void Player::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::vec2 Player::getPosition()
{
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
}

float Player::getPosLevel() {
	return posLevel;
}

bool Player::isWalking() {
	if (movimiento == 2 || movimiento == 3 || movimiento == 6 || movimiento == 7) return true;
	else return false;
}


bool Player::isRunning() {
	if (movimiento == 10 || movimiento == 6 || movimiento == 7) return true;
	else return false;
}

bool Player::isKicking_left() {
	if (movimiento == 8) return true;
	else return false;
}
bool Player::isKicking_right() {
	if (movimiento == 9) return true;
	else return false;
}
bool Player::isPunching_left() {
	if (movimiento == 5) return true;
	else return false;
}
bool Player::isPunching_right() {
	if (movimiento == 4) return true;
	else return false;
}
bool Player::isPunching_up_left() {
	if (movimiento == 12) return true;
	else return false;
}
bool Player::isPunching_up_right() {
	if (movimiento == 11) return true;
	else return false;
}
bool Player::isRecuperando() {
	if (recuperando > 0) return true;
	else return false;
}
bool Player::isJumping() {
	return bJumping;
}

void Player::recibirPuñetazoIzquierda() {
	if (vida > 0 && movimiento != 13) {
		if (sprite_recibir_izq->animation() != 0 && movimiento != 13) sprite_recibir_izq->changeAnimation(0);
		movimiento = 13;
		vida -= 10;
		++hits;
	}

	else if (vida > 0 && movimiento == 13) {
		++hits;
		vida -= 10;
	}

	if (vida > 0 && (movimiento == 13) && hits == 5) {
		hits = 0;
		sprite_recibir_izq->changeAnimation(2);
		recuperando = 0;
	}

}

void Player::recibirPuñetazoDerecha() {
	if (vida > 0 && movimiento != 14) {
		if (sprite_recibir->animation() != 0 && movimiento != 14) sprite_recibir->changeAnimation(0);
		movimiento = 14;
		vida -= 10;
		++hits;
	}

	else if (vida > 0 && movimiento == 14) {
		++hits;
		vida -= 10;
	}

	if (vida > 0 && (movimiento == 14) && hits == 5) {
		hits = 0;
		sprite_recibir->changeAnimation(2);
		recuperando = 0;
	}
}

void Player::turnToWalk() {
	if (vida > 0) {
		if (movimiento == 13) movimiento = 0;
		else movimiento = 1;
	}
}

int Player::getVida() {
	return vida;
}


