#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Enemigo3.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define FALL_STEP 4

void Enemigo3::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	mapShader = shaderProgram;
	vida = 500;
	movimiento = 1;
	spritesheet_enemigo.loadFromFile("images/Enemigo3/Enemigo3_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo = Sprite::createSprite(glm::ivec2(130, 160), glm::vec2(0.0204081633, 1), &spritesheet_enemigo, &shaderProgram);
	sprite_enemigo->setNumberAnimations(12);
	//quieto
	sprite_enemigo->setAnimationSpeed(0, 8);
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0204081633 * 0, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0204081633 * 1, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0204081633 * 2, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0204081633 * 3, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0204081633 * 4, 0.f));
	//caminar
	sprite_enemigo->setAnimationSpeed(1, 8);
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0204081633 * 5, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0204081633 * 6, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0204081633 * 7, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0204081633 * 8, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0204081633 * 9, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0204081633 * 10, 0.f));
	//correr
	sprite_enemigo->setAnimationSpeed(2, 8);
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0204081633 * 5, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0204081633 * 6, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0204081633 * 7, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0204081633 * 8, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0204081633 * 9, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0204081633 * 10, 0.f));
	//patada
	sprite_enemigo->setAnimationSpeed(3, 8);

	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 36, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 37, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 38, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 39, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 40, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 41, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 42, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 43, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 44, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 45, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 46, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 47, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0204081633 * 48, 0.f));
	//puñetazo
	sprite_enemigo->setAnimationSpeed(4, 8);
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 36, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 37, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 38, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 39, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 40, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 41, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 42, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 43, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 44, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 45, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 46, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 47, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0204081633 * 48, 0.f));
	//recibir
	sprite_enemigo->setAnimationSpeed(5, 6);
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0204081633 * 11, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0204081633 * 12, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0204081633 * 13, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0204081633 * 14, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0204081633 * 15, 0.f));
	//recibir
	sprite_enemigo->setAnimationSpeed(6, 6);
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0204081633 * 11, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0204081633 * 12, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0204081633 * 13, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0204081633 * 14, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0204081633 * 15, 0.f));
	//morir
	sprite_enemigo->setAnimationSpeed(7, 7);
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 16, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 17, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 18, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 19, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 20, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 21, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 22, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 23, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 24, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 25, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 26, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 27, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 28, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 29, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 30, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 31, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 32, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 33, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 34, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0204081633 * 35, 0.f));
	//quedarse en el suelo
	sprite_enemigo->setAnimationSpeed(8, 7);
	sprite_enemigo->addKeyframe(8, glm::vec2(0.0204081633 * 35, 0.f));
	//recibir
	sprite_enemigo->setAnimationSpeed(9, 6);
	sprite_enemigo->addKeyframe(9, glm::vec2(0.0204081633 * 30, 0.f));
	sprite_enemigo->addKeyframe(9, glm::vec2(0.0204081633 * 31, 0.f));
	//recibir
	sprite_enemigo->setAnimationSpeed(10, 6);
	sprite_enemigo->addKeyframe(10, glm::vec2(0.0204081633 * 34, 0.f));
	sprite_enemigo->addKeyframe(10, glm::vec2(0.0204081633 * 35, 0.f));
	//recuperar
	sprite_enemigo->setAnimationSpeed(11, 10);
	sprite_enemigo->addKeyframe(11, glm::vec2(0.0204081633 * 36, 0.f));
	sprite_enemigo->addKeyframe(11, glm::vec2(0.0204081633 * 37, 0.f));
	sprite_enemigo->addKeyframe(11, glm::vec2(0.0204081633 * 38, 0.f));



	spritesheet_enemigo_left.loadFromFile("images/Enemigo3/Enemigo3_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo_left = Sprite::createSprite(glm::ivec2(130, 160), glm::vec2(0.0204081633, 1), &spritesheet_enemigo_left, &shaderProgram);
	sprite_enemigo_left->setNumberAnimations(12);

	sprite_enemigo_left->setAnimationSpeed(0, 8);
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0204081633 * 48, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0204081633 * 47, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0204081633 * 46, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0204081633 * 45, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0204081633 * 44, 0.f));

	sprite_enemigo_left->setAnimationSpeed(1, 8);
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0204081633 * 43, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0204081633 * 42, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0204081633 * 41, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0204081633 * 40, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0204081633 * 39, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0204081633 * 38, 0.f));

	sprite_enemigo_left->setAnimationSpeed(2, 8);
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0204081633 * 43, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0204081633 * 42, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0204081633 * 41, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0204081633 * 40, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0204081633 * 39, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0204081633 * 38, 0.f));

	sprite_enemigo_left->setAnimationSpeed(3, 8);
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 12, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 11, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 10, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 9, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 8, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 7, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 6, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 5, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 4, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 3, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 2, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 1, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0204081633 * 0, 0.f));

	sprite_enemigo_left->setAnimationSpeed(4, 8);
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 12, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 11, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 10, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 9, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 8, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 7, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 6, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 5, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 4, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 3, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 2, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 1, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0204081633 * 0, 0.f));

	sprite_enemigo_left->setAnimationSpeed(5, 6);
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0204081633 * 37, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0204081633 * 36, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0204081633 * 35, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0204081633 * 34, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0204081633 * 33, 0.f));

	sprite_enemigo_left->setAnimationSpeed(6, 6);
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0204081633 * 37, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0204081633 * 36, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0204081633 * 35, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0204081633 * 34, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0204081633 * 33, 0.f));

	sprite_enemigo_left->setAnimationSpeed(7, 7);
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 32, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 31, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 30, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 29, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 28, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 27, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 26, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 25, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 24, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 23, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 22, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 21, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 20, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 19, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 18, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 17, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 16, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 15, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 14, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0204081633 * 13, 0.f));


	sprite_enemigo_left->setAnimationSpeed(8, 7);
	sprite_enemigo_left->addKeyframe(8, glm::vec2(0.0204081633 * 10, 0.f));

	sprite_enemigo_left->setAnimationSpeed(9, 6);
	sprite_enemigo_left->addKeyframe(9, glm::vec2(0.0204081633 * 30, 0.f));
	sprite_enemigo_left->addKeyframe(9, glm::vec2(0.0204081633 * 29, 0.f));

	sprite_enemigo_left->setAnimationSpeed(10, 6);
	sprite_enemigo_left->addKeyframe(10, glm::vec2(0.0204081633 * 26, 0.f));
	sprite_enemigo_left->addKeyframe(10, glm::vec2(0.0204081633 * 25, 0.f));

	sprite_enemigo_left->setAnimationSpeed(11, 10);
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 24, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 23, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 22, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 21, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 20, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 19, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 18, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 17, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 16, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 15, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 14, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 13, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 12, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 11, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 10, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 9, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 8, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 7, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 6, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 5, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 4, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 3, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 2, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 1, 0.f));
	sprite_enemigo_left->addKeyframe(11, glm::vec2(0.0204081633 * 0, 0.f));





	sprite_enemigo->changeAnimation(0);
	sprite_enemigo_left->changeAnimation(0);

	//tileMapDispl = tileMapPos;
}

void Enemigo3::update(int deltaTime)
{

	sprite_enemigo->update(deltaTime);
	sprite_enemigo_left->update(deltaTime);



	if (sprite_enemigo_left->animation() == 7 || sprite_enemigo->animation() == 7 || sprite_enemigo->animation() == 8) deltaTimeDeath += deltaTime;

	else if (sprite_enemigo_left->animation() == 5 || sprite_enemigo_left->animation() == 6 || sprite_enemigo->animation() == 6 || sprite_enemigo->animation() == 5) hitTime += deltaTime;

	else if ((sprite_enemigo_left->animation() == 11 || sprite_enemigo->animation() == 11) && (!sprite_enemigo_left->isFinalized() || !sprite_enemigo->isFinalized())) {
		if (movimiento == 1 && restablecer < 1200 && posPlayer.x < 580) posPlayer.x += 1;
		else if (restablecer < 1200 && posPlayer.x > 0) posPlayer.x -= 1;
		restablecer += deltaTime;
	}

	else if ((sprite_enemigo_left->animation() == 11 || sprite_enemigo->animation() == 11) && (sprite_enemigo_left->isFinalized() && sprite_enemigo->isFinalized())) {
		sprite_enemigo->changeAnimation(0);
		sprite_enemigo_left->changeAnimation(0);
		restablecer = 0;
	}


	if (hitTime > 500 && sprite_enemigo->animation() != 8 && sprite_enemigo_left->animation() != 8 && sprite_enemigo->animation() != 7 && sprite_enemigo_left->animation() != 7 && !sprite_enemigo_left->animation() != 11 && !sprite_enemigo->animation() != 11) {
		if (sprite_enemigo->animation() != 0 || sprite_enemigo_left->animation() != 0) {
			sprite_enemigo->changeAnimation(0);
			sprite_enemigo_left->changeAnimation(0);
			hitTime = 0;
			mciSendString(TEXT("stop sounds/SOUND/puñetazos.mp3"), NULL, 0, NULL);
			mciSendString(TEXT("stop sounds/SOUND/patada.mp3"), NULL, 0, NULL);
		}
	}

	if (movimiento == 0 && sprite_enemigo->animation() == 7 && deltaTimeDeath >= 2000) {
		sprite_enemigo->changeAnimation(8);
	}

	else if (movimiento == 1 && sprite_enemigo_left->animation() == 7 && deltaTimeDeath >= 2000) {
		sprite_enemigo_left->changeAnimation(8);
	}

	if (sprite_enemigo->animation() == 8 || sprite_enemigo_left->animation() == 8) timeAfterDeath += deltaTime;

	if (sprite_enemigo->animation() == 7 && movimiento == 0) {
		posPlayer.x -= 1;
		//posPlayer.y += 0.1f;
	}

	if (sprite_enemigo_left->animation() == 7 && movimiento == 1) {
		posPlayer.x += 1;
		//posPlayer.y += 0.1f;
	}

	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_enemigo_left->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

void Enemigo3::render()
{
	if (!isDeath()) {
		switch (movimiento)
		{
		case 0:
			sprite_enemigo->render();
			break;
		case 1:
			sprite_enemigo_left->render();
			break;
		}
	}
	else {
		if (parpadeo < 3 && muriendo < 150) {
			switch (movimiento)
			{
			case 0:
				sprite_enemigo->render();
				break;
			case 1:
				sprite_enemigo_left->render();
				break;
			}
		}
		++parpadeo;
		if (parpadeo == 10) parpadeo = 0;
		++muriendo;
	}
}

void Enemigo3::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
}

void Enemigo3::recibirPuñetazoIzquierda() {
	if (vida > 0 && sprite_enemigo_left->animation() != 7 && sprite_enemigo_left->animation() != 8) {
		movimiento = 1;
		if (sprite_enemigo_left->animation() != 5) sprite_enemigo_left->changeAnimation(5);
		hitTime = 0;
		if (golpe == 2) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			golpe = 0;
			vida -= 5;
		}
		else ++golpe;
	}
	if (vida <= 0 && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 8) && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_Enemigo3.mp3"), NULL, 0, NULL);
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
	else if (sprite_enemigo_left->isFinalized() && sprite_enemigo_left->animation() != 7 && sprite_enemigo_left->animation() != 8) sprite_enemigo_left->changeAnimation(9);
}
void Enemigo3::recibirPatadaIzquierda() {
	if (vida > 0 && sprite_enemigo_left->animation() != 7 && (sprite_enemigo_left->animation() != 8)) {
		movimiento = 1;
		if (golpe == 0) sprite_enemigo_left->changeAnimation(6);
		hitTime = 0;
		if (golpe == 0) {
			//mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 20;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 8) && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_Enemigo3.mp3"), NULL, 0, NULL);
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
	else if (sprite_enemigo_left->isFinalized()) sprite_enemigo_left->changeAnimation(10);
}
void Enemigo3::recibirPuñetazoDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 7 && (sprite_enemigo->animation() != 8)) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 5) sprite_enemigo->changeAnimation(5);
		hitTime = 0;
		if (golpe == 2) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			golpe = 0;
			vida -= 5;
		}
		else ++golpe;
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 8) && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_Enemigo3.mp3"), NULL, 0, NULL);
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
	else if (sprite_enemigo->isFinalized()) sprite_enemigo->changeAnimation(9);
}
void Enemigo3::recibirPatadaDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 7 && sprite_enemigo->animation() != 8) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 6) sprite_enemigo->changeAnimation(6);
		hitTime = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 20;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 8) && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_Enemigo3.mp3"), NULL, 0, NULL);
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
	else if (sprite_enemigo->isFinalized() && sprite_enemigo->animation() != 7 && sprite_enemigo->animation() != 8) sprite_enemigo->changeAnimation(10);
}

void Enemigo3::recibirPuñetazoArribaDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 7 && (sprite_enemigo->animation() != 8)) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 11) sprite_enemigo->changeAnimation(11);
		restablecer = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 25;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 8) && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_Enemigo3.mp3"), NULL, 0, NULL);
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
	else if (sprite_enemigo->isFinalized()) sprite_enemigo->changeAnimation(10);
}

void Enemigo3::recibirPuñetazoArribaIzquierda() {
	if (vida > 0 && sprite_enemigo->animation() != 7 && (sprite_enemigo->animation() != 8)) {
		movimiento = 1;
		if (sprite_enemigo_left->animation() != 11) sprite_enemigo_left->changeAnimation(11);
		restablecer = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 20;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 8) && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_Enemigo3.mp3"), NULL, 0, NULL);
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
	else if (sprite_enemigo->isFinalized()) sprite_enemigo->changeAnimation(10);
}



bool Enemigo3::isDying() {
	if ((sprite_enemigo->animation() == 7 || sprite_enemigo_left->animation() == 7 || (sprite_enemigo->animation() == 8 || sprite_enemigo_left->animation() == 8)) && vida <= 0) {
		return true;
	}
	return false;
}
bool Enemigo3::isDeath() {
	if ((sprite_enemigo->animation() == 8 || sprite_enemigo_left->animation() == 8) && timeAfterDeath > 1000 & vida <= 0) {
		return true;
	}
	return false;
}

bool Enemigo3::isCompletlyDeath() {
	if (muriendo >= 150) {
		return true;
	}
	return false;
}

void Enemigo3::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::vec2 Enemigo3::getPosition()
{
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
}

void Enemigo3::free() {
	sprite_enemigo->free();
	sprite_enemigo_left->free();
}


void Enemigo3::atacarPuñetazosDerecha() {
	if (sprite_enemigo->animation() != 3 && sprite_enemigo->animation() != 6 && sprite_enemigo->animation() != 5 && sprite_enemigo->animation() != 7 && sprite_enemigo->animation() != 8 && sprite_enemigo->animation() != 9 && sprite_enemigo->animation() != 10 && sprite_enemigo->animation() != 11 && vida > 0) {
		sprite_enemigo->changeAnimation(3);
		movimiento = 0;
		mciSendString(TEXT("play sounds/SOUND/fireBall.mp3"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("play sounds/SOUND/fireBall.mp3"), NULL, 0, NULL);
	}
}
void Enemigo3::atacarPuñetadosIzquierda() {
	if (sprite_enemigo_left->animation() != 3 && sprite_enemigo_left->animation() != 5 && sprite_enemigo_left->animation() != 6 && sprite_enemigo_left->animation() != 8 && sprite_enemigo_left->animation() != 9 && sprite_enemigo_left->animation() != 10 && sprite_enemigo_left->animation() != 11 && vida > 0) {
		sprite_enemigo_left->changeAnimation(3);
		movimiento = 1;
		mciSendString(TEXT("play sounds/SOUND/fireBall.mp3"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("play sounds/SOUND/fireBall.mp3"), NULL, 0, NULL);
	}
}

bool Enemigo3::isPunchingRight() {
	if (sprite_enemigo->animation() == 3 && movimiento == 0) return true;
	return false;
}

bool Enemigo3::isPunchingLeft() {
	if (sprite_enemigo_left->animation() == 3 && movimiento == 1) return true;
	return false;
}

void Enemigo3::turnToWalk() {
	if (sprite_enemigo->animation() == 3 && movimiento == 0 && sprite_enemigo_left->isFinalized()) sprite_enemigo->changeAnimation(0);
	if (sprite_enemigo_left->animation() == 3 && movimiento == 1 && sprite_enemigo->isFinalized()) sprite_enemigo_left->changeAnimation(0);
	mciSendString(TEXT("stop sounds/SOUND/fireBall.mp3"), NULL, 0, NULL);
}

bool Enemigo3::isRecuperando() {
	if (sprite_enemigo_left->animation() == 11 && movimiento == 1) return true;
	else if (sprite_enemigo->animation() == 11 && movimiento == 0) return true;
	return false;
}

void Enemigo3::setGolpesto0() {
	golpe = 0;
}

void Enemigo3::moverse(float xP, float yP) {
	if (vida > 0 && (sprite_enemigo->animation() == 0 || sprite_enemigo_left->animation() == 0 || sprite_enemigo->animation() == 1 || sprite_enemigo_left->animation() == 1)) {
		if (estaCerca(xP, yP) && (sprite_enemigo->animation() == 0 || sprite_enemigo_left->animation() == 0 || sprite_enemigo->animation() == 1 || sprite_enemigo_left->animation() == 1)) {
			if (sprite_enemigo->animation() == 0 || sprite_enemigo_left->animation() == 0) {
				if (movimiento == 1) {
					if (posPlx(xP) == 0) {
						posPlayer.x -= 1;
					}
					else {
						movimiento = 0;
						posPlayer.x += 1;
					}
					if (posPly(yP) == 0) posPlayer.y -= 1;
					else posPlayer.y += 1;
					sprite_enemigo_left->changeAnimation(1);
					sprite_enemigo->changeAnimation(1);
				}

				else {
					if (posPlx(xP) == 0) {
						movimiento = 1;
						posPlayer.x -= 1;
					}
					else {
						posPlayer.x += 1;
					}
					if (posPly(yP) == 0) posPlayer.y -= 1;
					else posPlayer.y += 1;
					sprite_enemigo_left->changeAnimation(1);
					sprite_enemigo->changeAnimation(1);
				}
			}
			else if (sprite_enemigo->animation() == 1 || sprite_enemigo_left->animation() == 1) {
				if (movimiento == 1) {
					if (posPlx(xP) == 0) {
						posPlayer.x -= 1;
					}
					else {
						movimiento = 0;
						posPlayer.x += 1;
					}
					if (posPly(yP) == 0) posPlayer.y -= 1;
					else posPlayer.y += 1;
				}

				else {
					if (posPlx(xP) == 0) {
						movimiento = 1;
						posPlayer.x -= 1;
					}
					else {
						posPlayer.x += 1;
					}
					if (posPly(yP) == 0) posPlayer.y -= 1;
					else posPlayer.y += 1;
				}
			}
		}
		else if (!estaCerca(xP, yP) && (sprite_enemigo->animation() == 1 || sprite_enemigo_left->animation() == 1)) {
			sprite_enemigo_left->changeAnimation(0);
			sprite_enemigo->changeAnimation(0);
		}
	}
}

bool Enemigo3::estaCerca(float xP, float yP)
{
	return ((abs(xP - posPlayer.x) < 200) && (abs(yP - posPlayer.y) < 200) && (abs(yP - posPlayer.y) >= 3) && (abs(xP - posPlayer.x) >= 3));
}

int Enemigo3::posPlx(float xP)
{
	if (xP <= posPlayer.x) {
		return 0;
	}
	else return 1;
}

int Enemigo3::posPly(float yP)
{
	if ((yP - 45) <= posPlayer.y) {
		return 0;
	}
	else return 1;
}