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
	if (lev == 1) {
		posIni = 2200;
		posFin = 2700;
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
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.11111111f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.22222222f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.33333333f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.44444444f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.55555555f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.66666666f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.77777777f, 0.f));
	sprite_saltar_derecha->addKeyframe(0, glm::vec2(0.88888888f, 0.f));

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

	spritesheet_recibir_daño.loadFromFile("images/Ramona/ramona_recibir.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_recibir = Sprite::createSprite(glm::ivec2(80, 120), glm::vec2(0.0344827586, 1), &spritesheet_recibir_daño, &shaderProgram);
	sprite_recibir->setNumberAnimations(5);

	sprite_recibir->setAnimationSpeed(0, 4);
	sprite_recibir->addKeyframe(0, glm::vec2(0, 0.f));
	sprite_recibir->addKeyframe(0, glm::vec2(0.0344827586, 0.f));
	sprite_recibir->addKeyframe(0, glm::vec2(0.0344827586 * 2, 0.f));

	sprite_recibir->setAnimationSpeed(1, 6);
	sprite_recibir->addKeyframe(1, glm::vec2(0.0344827586 * 3, 0.f));
	sprite_recibir->addKeyframe(1, glm::vec2(0.0344827586 * 4, 0.f));
	sprite_recibir->addKeyframe(1, glm::vec2(0.0344827586 * 5, 0.f));
	sprite_recibir->addKeyframe(1, glm::vec2(0.0344827586 * 6, 0.f));

	sprite_recibir->setAnimationSpeed(2, 10);
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 7, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 8, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 9, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 10, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 11, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 12, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 13, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 14, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 15, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 16, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 17, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 18, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 19, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 20, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 21, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 22, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 23, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 24, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 25, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 26, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 27, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 28, 0.f));

	sprite_recibir->setAnimationSpeed(3, 10);
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 7, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 8, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 9, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 10, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 11, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 12, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 13, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 14, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 15, 0.f));
	sprite_recibir->addKeyframe(3, glm::vec2(0.0344827586 * 16, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 17, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 18, 0.f));
	sprite_recibir->addKeyframe(2, glm::vec2(0.0344827586 * 19, 0.f));

	sprite_recibir->setAnimationSpeed(4, 10);
	sprite_recibir->addKeyframe(4, glm::vec2(0.0344827586 * 19, 0.f));


	spritesheet_recibir_daño_izq.loadFromFile("images/Ramona/ramona_recibir_izq.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_recibir_izq = Sprite::createSprite(glm::ivec2(80, 130), glm::vec2(0.0344827586, 1), &spritesheet_recibir_daño_izq, &shaderProgram);
	sprite_recibir_izq->setNumberAnimations(5);

	sprite_recibir_izq->setAnimationSpeed(0, 4);
	sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0344827586 * 28, 0.f));
	sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0344827586 * 27, 0.f));
	sprite_recibir_izq->addKeyframe(0, glm::vec2(0.0344827586 * 26, 0.f));

	sprite_recibir_izq->setAnimationSpeed(1, 6);
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0344827586 * 25, 0.f));
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0344827586 * 24, 0.f));
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0344827586 * 23, 0.f));
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0344827586 * 22, 0.f));

	sprite_recibir_izq->setAnimationSpeed(2, 10);
	sprite_recibir_izq->addKeyframe(1, glm::vec2(0.0344827586 * 21, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 20, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 19, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 18, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 17, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 16, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 15, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 14, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 13, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 12, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 11, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 10, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 9, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 8, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 7, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 6, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 5, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 4, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 3, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 2, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 1, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 0, 0.f));

	sprite_recibir_izq->setAnimationSpeed(3, 10);
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 20, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 19, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 18, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 17, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 16, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 15, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 14, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 13, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 12, 0.f));
	sprite_recibir_izq->addKeyframe(3, glm::vec2(0.0344827586 * 11, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 10, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 9, 0.f));
	sprite_recibir_izq->addKeyframe(2, glm::vec2(0.0344827586 * 8, 0.f));


	sprite_recibir_izq->setAnimationSpeed(4, 10);
	sprite_recibir_izq->addKeyframe(4, glm::vec2(0.0344827586 * 8, 0.f));




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
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
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
	sprite_recibir_izq->update(deltaTime);
	sprite_recibir->update(deltaTime);

	if (vida <= 0) {
		if (movimiento == 13 && sprite_recibir_izq->animation() != 3 && sprite_recibir_izq->animation() != 4) sprite_recibir_izq->changeAnimation(3);
		else if (movimiento == 14 && sprite_recibir->animation() != 3 && sprite_recibir->animation() != 4) sprite_recibir->changeAnimation(3);
		else if (!sprite_recibir_izq->isFinalized() && sprite_recibir_izq->animation() != 4) posPlayer.x += 1.5f;
		else if (!sprite_recibir->isFinalized() && sprite_recibir->animation() != 4) posPlayer.x -= 1.5f;
		if (sprite_recibir->animation() != 4 && sprite_recibir_izq->animation() != 4) posPlayer.y += 0.6;
		if (movimiento == 13 && sprite_recibir_izq->isFinalized()) {
			sprite_recibir_izq->changeAnimation(4);
		}
		else if (movimiento == 14 && sprite_recibir->isFinalized()) {
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


		if (sprite_pegando_derecha->isFinalized() && sprite_pegando_izquierda->isFinalized() && sprite_martillo->isFinalized() && sprite_martillo_iz->isFinalized() && sprite_rayo_derecha->isFinalized() && sprite_rayo_izquierda->isFinalized() && movimiento != 13 && movimiento != 14) {
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
					derecha = false;
					if (!bJumping) movimiento = 10;
					if (!sprite_correr_iz->animation() == 0) sprite_correr_iz->changeAnimation(0);
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
					derecha = true;
					if (!bJumping) movimiento = 10;
					if (!sprite_correr->animation() == 0) sprite_correr->changeAnimation(0);
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
	sprite_rayo_derecha->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_rayo_izquierda->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_correr->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_correr_iz->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_martillo->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_martillo_iz->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y)));
	sprite_recibir->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y - 15)));
	sprite_recibir_izq->setPosition(glm::vec2(float(posPlayer.x - 20), float(posPlayer.y - 15)));
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
	case 13:
		sprite_recibir_izq->render();
		break;
	case 14:
		sprite_recibir->render();
		break;
	}
}

void Ramona::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
}

void Ramona::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::vec2 Ramona::getPosition()
{
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
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
	else return false;
}
bool Ramona::isKicking_right() {
	if (movimiento == 9) return true;
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
bool Ramona::isPunching_up_left() {
	if (movimiento == 12) return true;
	else return false;
}
bool Ramona::isPunching_up_right() {
	if (movimiento == 11) return true;
	else return false;
}
bool Ramona::isRecuperando() {
	if (recuperando > 0) return true;
	else return false;
}
bool Ramona::isJumping() {
	return bJumping;
}

void Ramona::recibirPuñetazoIzquierda() {
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

void Ramona::recibirPuñetazoDerecha() {
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

void Ramona::turnToWalk() {
	if (vida > 0) {
		if (movimiento == 13) movimiento = 0;
		else movimiento = 1;
	}
}

int Ramona::getVida() {
	return vida;
}


