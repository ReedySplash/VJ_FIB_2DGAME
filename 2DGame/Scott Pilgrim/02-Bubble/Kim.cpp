#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Kim.h"
#include "Kim.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum KimAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Kim::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lev)
{
	level = lev;
	if (lev == 1) {
		posIni = 2200;
		posFin = 2300;
	}
	else {
		posIni = 2200;
		posFin = 2970;
	}
	vida = 100;
	posLevel = 75;
	mapShader = shaderProgram;
	movimiento = 0;
	bJumping = false;

	spritesheet.loadFromFile("images/Kim/Kim_stand_right.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(42, 100), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.75, 0.f));

	spritesheet_standLeft.loadFromFile("images/Kim/Kim_stand_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_standLeft = Sprite::createSprite(glm::ivec2(42, 100), glm::vec2(0.25, 1), &spritesheet_standLeft, &shaderProgram);
	sprite_standLeft->setNumberAnimations(4);

	sprite_standLeft->setAnimationSpeed(STAND_LEFT, 8);
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.75, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.5, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0.25, 0.f));
	sprite_standLeft->addKeyframe(STAND_LEFT, glm::vec2(0, 0.f));



	spritesheet_caminando.loadFromFile("images/Kim/Kim_walk_right.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.1666666667, 1), &spritesheet_caminando, &shaderProgram);
	sprite_caminando->setNumberAnimations(4);


	sprite_caminando->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666666667, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333333333, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.6777777777, 0.f));
	sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.83333333333, 0.f));

	spritesheet_caminando_izq.loadFromFile("images/Kim/Kim_walk_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando_izq = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.1666666667, 1), &spritesheet_caminando_izq, &shaderProgram);
	sprite_caminando_izq->setNumberAnimations(4);


	sprite_caminando_izq->setAnimationSpeed(MOVE_LEFT, 8);
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.833333333, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.6777777777, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.3333333333, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.1666666667, 0.f));
	sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	spritesheet_pegando_derecha.loadFromFile("images/Kim/Kim_puñetazos_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_pegando_derecha = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.0833333333, 1), &spritesheet_pegando_derecha, &shaderProgram);
	sprite_pegando_derecha->setNumberAnimations(1);

	sprite_pegando_derecha->setAnimationSpeed(0, 10);
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333, 0.f));
	sprite_pegando_derecha->addKeyframe(0, glm::vec2(0.083333333 * 2, 0.f));
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
	sprite_pegando_izquierda = Sprite::createSprite(glm::ivec2(70, 100), glm::vec2(0.083333333, 1), &spritesheet_pegando_izquierda, &shaderProgram);
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
	sprite_saltar_derecha = Sprite::createSprite(glm::ivec2(65, 110), glm::vec2(0.0769230769, 1), &spritesheet_saltar_derecha, &shaderProgram);
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
	sprite_saltar_izquierda = Sprite::createSprite(glm::ivec2(65, 110), glm::vec2(0.0769230769, 1), &spritesheet_saltar_izquierda, &shaderProgram);
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
	sprite_patada_derecha = Sprite::createSprite(glm::ivec2(75, 105), glm::vec2(0.142857143, 1), &spritesheet_patada_derecha, &shaderProgram);
	sprite_patada_derecha->setNumberAnimations(1);

	sprite_patada_derecha->setAnimationSpeed(0, 10);
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143 * 2, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143 * 3, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143 * 4, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143 * 5, 0.f));
	sprite_patada_derecha->addKeyframe(0, glm::vec2(0.142857143 * 6, 0.f));

	spritesheet_patada_izquierda.loadFromFile("images/Kim/Kim_patada_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_patada_izquierda = Sprite::createSprite(glm::ivec2(75, 105), glm::vec2(0.142857143, 1), &spritesheet_patada_izquierda, &shaderProgram);
	sprite_patada_izquierda->setNumberAnimations(1);

	sprite_patada_izquierda->setAnimationSpeed(0, 10);
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143 * 6, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143 * 5, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143 * 4, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143 * 3, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143 * 2, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0.142857143, 0.f));
	sprite_patada_izquierda->addKeyframe(0, glm::vec2(0, 0.f));

	spritesheet_correr.loadFromFile("images/Kim/kim_run.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_correr = Sprite::createSprite(glm::ivec2(60, 100), glm::vec2(0.0625, 1), &spritesheet_correr, &shaderProgram);
	sprite_correr->setNumberAnimations(2);

	sprite_correr->setAnimationSpeed(0, 10);
	sprite_correr->addKeyframe(0, glm::vec2(0, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.0625, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.0625 * 2, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.0625 * 3, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.0625 * 4, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.0625 * 5, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.0625 * 6, 0.f));
	sprite_correr->addKeyframe(0, glm::vec2(0.0625 * 7, 0.f));

	sprite_correr->setAnimationSpeed(1, 10);
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 8, 0.f));
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 9, 0.f));
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 10, 0.f));
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 11, 0.f));
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 12, 0.f));
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 13, 0.f));
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 14, 0.f));
	sprite_correr->addKeyframe(1, glm::vec2(0.0625 * 15, 0.f));

	spritesheet_puñetazo_arriba.loadFromFile("images/Kim/kim_escp_right.png", TEXTURE_PIXEL_FORMAT_RGBA);
	puñetazo_arriba = Sprite::createSprite(glm::ivec2(150, 100), glm::vec2(0.0833333333, 1), &spritesheet_puñetazo_arriba, &shaderProgram);
	puñetazo_arriba->setNumberAnimations(1);

	puñetazo_arriba->setAnimationSpeed(0, 12);
	puñetazo_arriba->addKeyframe(0, glm::vec2(0, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 2, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 3, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 4, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 5, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 6, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 7, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 8, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 9, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 10, 0.f));
	puñetazo_arriba->addKeyframe(0, glm::vec2(0.0833333333 * 11, 0.f));

	spritesheet_puñetazo_arriba_izq.loadFromFile("images/Kim/kim_escp_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	puñetazo_arriba_izq = Sprite::createSprite(glm::ivec2(150, 100), glm::vec2(0.0833333333, 1), &spritesheet_puñetazo_arriba_izq, &shaderProgram);
	puñetazo_arriba_izq->setNumberAnimations(1);

	puñetazo_arriba_izq->setAnimationSpeed(0, 12);
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 11, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 10, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 9, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 8, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 7, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 6, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 5, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 4, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 3, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333 * 2, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0.0833333333, 0.f));
	puñetazo_arriba_izq->addKeyframe(0, glm::vec2(0, 0.f));

	spritesheet_recibir_daño.loadFromFile("images/Kim/recibir_daño.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_recibir = Sprite::createSprite(glm::ivec2(80, 120), glm::vec2(0.0434782609, 1), &spritesheet_recibir_daño, &shaderProgram);
	sprite_recibir->setNumberAnimations(5);

	sprite_recibir->setAnimationSpeed(0, 4);
	sprite_recibir->addKeyframe(0, glm::vec2(0.0434782609 * 0, 0.f));
	sprite_recibir->addKeyframe(0, glm::vec2(0.0434782609, 0.f));
	sprite_recibir->addKeyframe(0, glm::vec2(0.0434782609 * 2, 0.f));

	sprite_recibir->setAnimationSpeed(1, 6);
	sprite_recibir->addKeyframe(1, glm::vec2(0.0434782609 * 2, 0.f));
	sprite_recibir->addKeyframe(1, glm::vec2(0.0434782609 * 3, 0.f));
	sprite_recibir->addKeyframe(1, glm::vec2(0.0434782609 * 4, 0.f));
	sprite_recibir->addKeyframe(1, glm::vec2(0.0434782609 * 5, 0.f));
	sprite_recibir->addKeyframe(1, glm::vec2(0.0434782609 * 6, 0.f));

	sprite_recibir->setAnimationSpeed(2, 10);
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 3, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 4, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 5, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 6, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 7, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 8, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 9, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 10, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 11, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 12, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 13, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 14, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 15, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 16, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 17, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 18, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 19, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 20, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 21, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0434782609 * 22, 0.f));

	sprite_recibir->setAnimationSpeed(3, 8);
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 3, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 4, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 5, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 6, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 7, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 8, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 9, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 10, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 11, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 12, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 13, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0434782609 * 14, 0.f));
	

	sprite_recibir->setAnimationSpeed(4, 10);
	sprite_recibir->addKeyframe(4, glm::vec2(0.0434782609 * 14, 0.f));
	

	spritesheet_recibir_daño_izq.loadFromFile("images/Kim/recibir_daño_izq.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_recibir_izq = Sprite::createSprite(glm::ivec2(80, 130), glm::vec2(0.0434782609, 1), &spritesheet_recibir_daño_izq, &shaderProgram);
	sprite_recibir_izq->setNumberAnimations(5);

	sprite_recibir_izq->setAnimationSpeed(0, 4);
	sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0434782609 * 22, 0.f));
	sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0434782609 * 21, 0.f));
	sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0434782609 * 20, 0.f));

	sprite_recibir_izq->setAnimationSpeed(1, 6);
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0434782609 * 25, 0.f));
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0434782609 * 24, 0.f));
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0434782609 * 23, 0.f));
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0434782609 * 22, 0.f));
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0434782609 * 21, 0.f));

	sprite_recibir_izq->setAnimationSpeed(2, 10);
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 19, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 18, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 17, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 16, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 15, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 14, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 13, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 12, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 11, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 10, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 9, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 8, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 7, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 6, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 5, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 4, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 3, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 2, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 1, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0434782609 * 0, 0.f));

	sprite_recibir_izq->setAnimationSpeed(3, 8);
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 19, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 18, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 17, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 16, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 15, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 14, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 13, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 12, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 11, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 10, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 9, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0434782609 * 8, 0.f));
	

	sprite_recibir_izq->setAnimationSpeed(4, 10);
	sprite_recibir_izq->addKeyframe(4, glm::vec2(0.0434782609 * 8, 0.f));


	sprite->changeAnimation(STAND_RIGHT);
	sprite_standLeft->changeAnimation(STAND_LEFT);
	sprite_caminando->changeAnimation(MOVE_RIGHT);
	sprite_caminando_izq->changeAnimation(MOVE_LEFT);
	sprite_correr->changeAnimation(0);
	//tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

void Kim::update(int deltaTime)
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
		else if (!sprite_recibir_izq->isFinalized() && sprite_recibir_izq->animation() != 4) posPlayer.x += 1.5f;
		else if (!sprite_recibir->isFinalized() && sprite_recibir->animation() != 4) posPlayer.x -= 1.5f;
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
			if (sprite_recibir->animation() == 2 && movimiento == 14 && recuperando < 1300) posPlayer.x -= 1.5f;
			else if (sprite_recibir_izq->animation() == 2 && movimiento == 13 && recuperando < 1300) posPlayer.x += 1.5f;
			if (recuperando < 1300) posPlayer.y += 0.25;
			else if (recuperando > 2160) {
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
					else if (posPlayer.x > 0 && posLevel > posIni) {
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
					else if (posPlayer.x < 580 && posLevel > posFin) {
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
				else if (posPlayer.x > 0 && posLevel > posIni) {
					posPlayer.x -= 2.f;
					posLevel -= 2.f;
				}
				else posLevel -= 2.f;
				if (posPlayer.x <= 0) posLevel += 2.f;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (!bJumping) movimiento = 3;
				if (posPlayer.x < 380 && posLevel >= 0) {
					posPlayer.x += 2.f;
					posLevel += 2.f;
				}
				else if (posPlayer.x < 580 && posLevel > posFin) {
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
	sprite_caminando->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_pegando_derecha->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_pegando_izquierda->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_saltar_derecha->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_saltar_izquierda->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_patada_derecha->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_patada_izquierda->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_correr->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	puñetazo_arriba->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	puñetazo_arriba_izq->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_recibir->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y - 15)));
	sprite_recibir_izq->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y - 15)));
}

void Kim::render()
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

void Kim::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
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

float Kim::getPosLevel() {
	return posLevel;
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
bool Kim::isPunching_up_left() {
	if (movimiento == 12) return true;
	else return false;
}
bool Kim::isPunching_up_right() {
	if (movimiento == 11) return true;
	else return false;
}
bool Kim::isRecuperando() {
	if (recuperando > 0) return true;
	else return false;
}
bool Kim::isJumping() {
	return bJumping;
}
bool Kim::isDead() {
	if (sprite_recibir_izq->animation() == 4 || sprite_recibir->animation() == 4) return true;
	return false;
}

void Kim::recibirPuñetazoIzquierda() {
	if (vida > 0 && movimiento != 13) {
		if (movimiento != 13) sprite_recibir_izq->changeAnimation(0);
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

void Kim::recibirPuñetazoDerecha() {
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

void Kim::turnToWalk() {
	if (vida > 0) {
		if (movimiento == 13) movimiento = 0;
		else movimiento = 1;
	}
}

int Kim::getVida() {
	return vida;
}

