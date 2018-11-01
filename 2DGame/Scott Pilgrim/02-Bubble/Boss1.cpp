#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Boss1.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define FALL_STEP 4


void Boss1::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	mapShader = shaderProgram;
	vida = 1500;
	movimiento = 1;
	spritesheet_enemigo.loadFromFile("images/Boss_level1/EnvyAdams.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo = Sprite::createSprite(glm::ivec2(100, 180), glm::vec2(0.0107526882, 1), &spritesheet_enemigo, &shaderProgram);
	sprite_enemigo->setNumberAnimations(8);

	//quieto
	sprite_enemigo->setAnimationSpeed(0, 8);
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0107526882 * 0, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0107526882 * 1, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0107526882 * 2, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0107526882 * 3, 0.f));
	//caminar
	sprite_enemigo->setAnimationSpeed(1, 8);
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0107526882 * 4, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0107526882 * 5, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0107526882 * 6, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0107526882 * 7, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0107526882 * 8, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0107526882 * 9, 0.f));
	//patada1
	sprite_enemigo->setAnimationSpeed(2, 8);
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0107526882 * 10, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0107526882 * 11, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0107526882 * 12, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0107526882 * 13, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0107526882 * 14, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0107526882 * 15, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0107526882 * 16, 0.f));
	//patada2
	sprite_enemigo->setAnimationSpeed(3, 8);
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0107526882 * 17, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0107526882 * 18, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0107526882 * 19, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0107526882 * 20, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0107526882 * 21, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0107526882 * 22, 0.f));
	//patada_arriba
	sprite_enemigo->setAnimationSpeed(4, 8);
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 23, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 24, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 25, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 26, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 27, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 28, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 29, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 30, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0107526882 * 31, 0.f));
	//recbir_daño
	sprite_enemigo->setAnimationSpeed(5, 6);
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0107526882 * 32, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0107526882 * 33, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0107526882 * 34, 0.f));

	//recibir y recuperar
	sprite_enemigo->setAnimationSpeed(6, 6);
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 35, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 36, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 37, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 38, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 39, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 40, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 41, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 42, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 43, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 44, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 45, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 46, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 47, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 48, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 49, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 50, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 51, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0107526882 * 52, 0.f));

	//morir
	sprite_enemigo->setAnimationSpeed(7, 12);
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 53, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 54, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 55, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 56, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 57, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 58, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 59, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 60, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 61, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 62, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 63, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 64, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 65, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 66, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 67, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 68, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 69, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 70, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 71, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 72, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 73, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 74, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 75, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 76, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 77, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 78, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 79, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 80, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 81, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 82, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 83, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 84, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 85, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 86, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 87, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 88, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 89, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 90, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 91, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0107526882 * 92, 0.f));


	spritesheet_enemigo_left.loadFromFile("images/Boss_level1/EnvyAdams_izq.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo_left = Sprite::createSprite(glm::ivec2(100, 180), glm::vec2(0.0107526882, 1), &spritesheet_enemigo_left, &shaderProgram);
	sprite_enemigo_left->setNumberAnimations(8);

	//quieto
	sprite_enemigo_left->setAnimationSpeed(0, 9);
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0107526882 * 92, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0107526882 * 91, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0107526882 * 90, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0107526882 * 89, 0.f));
	//caminar
	sprite_enemigo_left->setAnimationSpeed(1, 9);
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0107526882 * 88, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0107526882 * 87, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0107526882 * 86, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0107526882 * 85, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0107526882 * 84, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0107526882 * 83, 0.f));
	//patada1
	sprite_enemigo_left->setAnimationSpeed(2, 10);
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0107526882 * 82, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0107526882 * 81, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0107526882 * 80, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0107526882 * 79, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0107526882 * 78, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0107526882 * 77, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0107526882 * 76, 0.f));
	//patada2
	sprite_enemigo_left->setAnimationSpeed(3, 10);
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0107526882 * 75, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0107526882 * 74, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0107526882 * 73, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0107526882 * 72, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0107526882 * 71, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0107526882 * 70, 0.f));
	//patada_arriba
	sprite_enemigo_left->setAnimationSpeed(4, 10);
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 69, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 68, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 67, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 66, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 65, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 64, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 63, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 62, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0107526882 * 61, 0.f));
	//recbir_daño
	sprite_enemigo_left->setAnimationSpeed(5, 10);
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0107526882 * 60, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0107526882 * 59, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0107526882 * 58, 0.f));

	//recibir y recuperar
	sprite_enemigo_left->setAnimationSpeed(6, 10);
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 57, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 56, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 55, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 54, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 53, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 52, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 51, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 50, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 49, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 48, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 47, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 46, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 45, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 44, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 43, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 42, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 41, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0107526882 * 40, 0.f));

	//morir
	sprite_enemigo_left->setAnimationSpeed(7, 12);
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 39, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 38, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 37, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 36, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 35, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 34, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 33, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 32, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 31, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 30, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 29, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 28, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 27, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 26, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 25, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 24, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 23, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 22, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 21, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 20, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 19, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 18, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 17, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 16, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 15, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 14, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 13, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 12, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 11, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 10, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 9, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 8, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 7, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 6, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 5, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 4, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 3, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 2, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0107526882 * 1, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0, 0.f));


	sprite_enemigo->changeAnimation(0);
	sprite_enemigo_left->changeAnimation(0);
}

void Boss1::update(int deltaTime)
{

	sprite_enemigo->update(deltaTime);
	sprite_enemigo_left->update(deltaTime);



	if (sprite_enemigo_left->animation() == 7 || sprite_enemigo->animation() == 7 ) deltaTimeDeath += deltaTime;

	else if (sprite_enemigo_left->animation() == 5 ||  sprite_enemigo->animation() == 5) hitTime += deltaTime;

	else if ((sprite_enemigo_left->animation() == 6 || sprite_enemigo->animation() == 6) && (!sprite_enemigo_left->isFinalized() || !sprite_enemigo->isFinalized())) {
		if (movimiento == 1 && restablecer < 1200 && posPlayer.x < 580) posPlayer.x += 1;
		else if (restablecer < 1200 && posPlayer.x > 0) posPlayer.x -= 1;
		restablecer += deltaTime;
	}

	else if ((sprite_enemigo_left->animation() == 6 || sprite_enemigo->animation() == 6) && (sprite_enemigo_left->isFinalized() && sprite_enemigo->isFinalized())) {
		sprite_enemigo->changeAnimation(0);
		sprite_enemigo_left->changeAnimation(0);
		restablecer = 0;
	}


	if (hitTime > 500  && sprite_enemigo->animation() != 6 && sprite_enemigo_left->animation() != 6 && !sprite_enemigo_left->animation() != 7 && !sprite_enemigo->animation() != 7) {
		if (sprite_enemigo->animation() != 0 || sprite_enemigo_left->animation() != 0) {
			sprite_enemigo->changeAnimation(0);
			sprite_enemigo_left->changeAnimation(0);
			hitTime = 0;
			mciSendString(TEXT("stop sounds/SOUND/puñetazos.mp3"), NULL, 0, NULL);
			mciSendString(TEXT("stop sounds/SOUND/patada.mp3"), NULL, 0, NULL);
		}
	}

	if (movimiento == 0 && sprite_enemigo->animation() == 7 && deltaTimeDeath >= 3200) {
		muerto = true;
	}

	else if (movimiento == 1 && sprite_enemigo_left->animation() == 7 && deltaTimeDeath >= 3200) {
		muerto = true;
	}

	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_enemigo_left->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

void Boss1::render()
{
	if (!muerto) {
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
}

void Boss1::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
}

void Boss1::recibirPuñetazoIzquierda() {
	if (vida > 0 && sprite_enemigo_left->animation() != 6 && sprite_enemigo_left->animation() != 7) {
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
		if (golpe == 10) golpe = 0;
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}
void Boss1::recibirPatadaIzquierda() {
	if (vida > 0 && sprite_enemigo_left->animation() != 6 && (sprite_enemigo_left->animation() != 7)) {
		movimiento = 1;
		if (golpe == 0) sprite_enemigo_left->changeAnimation(5);
		hitTime = 0;
		if (golpe == 0) {
			//mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 20;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}
void Boss1::recibirPuñetazoDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 6 && (sprite_enemigo->animation() != 7)) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 5) sprite_enemigo->changeAnimation(5);
		hitTime = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 5;
			++golpe;
		}
		else ++golpe;
		if (golpe == 10) golpe = 0;
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
	
}
void Boss1::recibirPatadaDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 6 && sprite_enemigo->animation() != 7) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 5) sprite_enemigo->changeAnimation(5);
		hitTime = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 20;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}

void Boss1::recibirPuñetazoArribaDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 6 && (sprite_enemigo->animation() != 7)) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 6) sprite_enemigo->changeAnimation(6);
		restablecer = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 25;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}

void Boss1::recibirPuñetazoArribaIzquierda() {
	if (vida > 0 && sprite_enemigo->animation() != 6 && (sprite_enemigo->animation() != 7)) {
		movimiento = 1;
		if (sprite_enemigo_left->animation() != 6) sprite_enemigo_left->changeAnimation(6);
		restablecer = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 20;
			++golpe;
		}
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}



bool Boss1::isDying() {
	if ((sprite_enemigo->animation() == 7 || sprite_enemigo_left->animation() == 7) && vida <= 0) {
		return true;
	}
	return false;
}
bool Boss1::isDeath() {
	if ((sprite_enemigo->animation() == 7 || sprite_enemigo_left->animation() == 7) && deltaTimeDeath > 3200 & vida <= 0) {
		return true;
	}
	return false;
}

bool Boss1::isCompletlyDeath() {
	if ((sprite_enemigo->animation() == 7 || sprite_enemigo_left->animation() == 7) && deltaTimeDeath > 3200) return true;
	return false;
}

void Boss1::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::vec2 Boss1::getPosition()
{
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
}

void Boss1::free() {
	sprite_enemigo->free();
	sprite_enemigo_left->free();
}


void Boss1::atacarPuñetazosDerecha() {
	if (sprite_enemigo->animation() != 2 && sprite_enemigo->animation() != 7 && sprite_enemigo->animation() != 6 && vida > 0) {
		sprite_enemigo->changeAnimation(2);
		movimiento = 0;
	}
}
void Boss1::atacarPuñetadosIzquierda() {
	if (sprite_enemigo_left->animation() != 2 && sprite_enemigo_left->animation() != 7 && sprite_enemigo_left->animation() != 6 && vida > 0) {
		sprite_enemigo_left->changeAnimation(2);
		movimiento = 1;
	}
}

bool Boss1::isPunchingRight() {
	if (sprite_enemigo->animation() == 2 && movimiento == 0) return true;
	return false;
}

bool Boss1::isPunchingLeft() {
	if (sprite_enemigo_left->animation() == 2 && movimiento == 1) return true;
	return false;
}

void Boss1::turnToWalk() {
	if (sprite_enemigo->animation() == 2 && movimiento == 0 && !sprite_enemigo->isFinalized()) sprite_enemigo->changeAnimation(0);
	if (sprite_enemigo_left->animation() == 2 && movimiento == 1 && !sprite_enemigo_left->isFinalized()) sprite_enemigo_left->changeAnimation(0);
}

bool Boss1::isRecuperando() {
	if (sprite_enemigo_left->animation() == 6 && movimiento == 1) return true;
	else if (sprite_enemigo->animation() == 6 && movimiento == 0) return true;
	if (sprite_enemigo_left->animation() == 5 && movimiento == 1 && hitTime < 500) return true;
	else if (sprite_enemigo->animation() == 5 && movimiento == 0 && hitTime < 500) return true;
	return false;
}

void Boss1::setGolpesto0() {
	golpe = 0;
}

void Boss1::moverse(float xP, float yP) {
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

bool Boss1::estaCerca(float xP, float yP)
{
	return ((abs(xP - posPlayer.x) < 200) && (abs(yP - posPlayer.y) < 200) && (abs(yP - posPlayer.y) >= 3) && (abs(xP - posPlayer.x) >= 3));
}

int Boss1::posPlx(float xP)
{
	if (xP <= posPlayer.x) {
		return 0;
	}
	else return 1;
}

int Boss1::posPly(float yP)
{
	if ((yP - 45) <= posPlayer.y) {
		return 0;
	}
	else return 1;
}