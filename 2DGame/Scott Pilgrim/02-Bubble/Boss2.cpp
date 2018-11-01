#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Boss2.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define FALL_STEP 4


void Boss2::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	mapShader = shaderProgram;
	vida = 1500;
	movimiento = 1;
	spritesheet_enemigo.loadFromFile("images/Boss2/Boss2_derecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo = Sprite::createSprite(glm::ivec2(100, 180), glm::vec2(0.0135135135, 1), &spritesheet_enemigo, &shaderProgram);
	sprite_enemigo->setNumberAnimations(8);

	//quieto
	sprite_enemigo->setAnimationSpeed(0, 8);
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0135135135 * 0, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0135135135 * 1, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0135135135 * 2, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0135135135 * 3, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0135135135 * 4, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0135135135 * 5, 0.f));
	//caminar
	sprite_enemigo->setAnimationSpeed(1, 8);
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0135135135 * 6, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0135135135 * 7, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0135135135 * 8, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0135135135 * 9, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0135135135 * 10, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0135135135 * 11, 0.f));
	//patada1
	sprite_enemigo->setAnimationSpeed(2, 8);
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 12, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 13, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 14, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 15, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 16, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 17, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 18, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0135135135 * 19, 0.f));
	//patada2
	sprite_enemigo->setAnimationSpeed(3, 8);
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 20, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 21, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 22, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 23, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 24, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 25, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 26, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 27, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0135135135 * 28, 0.f));
	//patada_arriba
	sprite_enemigo->setAnimationSpeed(4, 8);
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 29, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 30, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 31, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 32, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 33, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 34, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 35, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0135135135 * 36, 0.f));
	//recbir_daño
	sprite_enemigo->setAnimationSpeed(5, 6);
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0135135135 * 37, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0135135135 * 38, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0135135135 * 39, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0135135135 * 40, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0135135135 * 41, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0135135135 * 42, 0.f));

	//recibir y recuperar
	sprite_enemigo->setAnimationSpeed(6, 6);
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 43, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 44, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 45, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 46, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 47, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 48, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 49, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 50, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 51, 0.f));

	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 52, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 53, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 54, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 55, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 56, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 57, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 58, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 59, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 60, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 61, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0135135135 * 62, 0.f));

	//morir
	sprite_enemigo->setAnimationSpeed(7, 7);
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 43, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 44, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 45, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 46, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 47, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 48, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 49, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 50, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 51, 0.f));

	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 63, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 64, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 65, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 66, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 67, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 68, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 69, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 70, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 71, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 72, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0135135135 * 73, 0.f));


	spritesheet_enemigo_left.loadFromFile("images/Boss2/Boss2_izquierda.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo_left = Sprite::createSprite(glm::ivec2(100, 180), glm::vec2(0.0135135135, 1), &spritesheet_enemigo_left, &shaderProgram);
	sprite_enemigo_left->setNumberAnimations(8);

	//quieto
	sprite_enemigo_left->setAnimationSpeed(0, 8);
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0135135135 * 73, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0135135135 * 72, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0135135135 * 71, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0135135135 * 70, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0135135135 * 69, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0135135135 * 68, 0.f));
	//caminar
	sprite_enemigo_left->setAnimationSpeed(1, 8);
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0135135135 * 67, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0135135135 * 66, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0135135135 * 65, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0135135135 * 64, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0135135135 * 63, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0135135135 * 62, 0.f));
	//patada1
	sprite_enemigo_left->setAnimationSpeed(2, 8);
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 61, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 60, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 59, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 58, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 57, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 56, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 55, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0135135135 * 54, 0.f));
	//patada2
	sprite_enemigo_left->setAnimationSpeed(3, 8);
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 53, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 52, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 51, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 50, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 49, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 48, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 47, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 46, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0135135135 * 45, 0.f));
	//patada_arriba
	sprite_enemigo_left->setAnimationSpeed(4, 8);
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 44, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 43, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 42, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 41, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 40, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 39, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 38, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0135135135 * 37, 0.f));
	//recbir_daño
	sprite_enemigo_left->setAnimationSpeed(5, 6);
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0135135135 * 36, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0135135135 * 35, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0135135135 * 34, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0135135135 * 33, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0135135135 * 32, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0135135135 * 31, 0.f));

	//recibir y recuperar
	sprite_enemigo_left->setAnimationSpeed(6, 6);
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 30, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 29, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 28, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 27, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 26, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 25, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 24, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 23, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 22, 0.f));

	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 21, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 20, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 19, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 18, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 17, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 16, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 15, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 14, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 13, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 12, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0135135135 * 11, 0.f));

	//morir
	sprite_enemigo_left->setAnimationSpeed(7, 7);
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 30, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 29, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 28, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 27, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 26, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 25, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 24, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 23, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 22, 0.f));

	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 10, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 9, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 8, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 7, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 6, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 5, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 4, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 3, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 2, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 1, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0135135135 * 0, 0.f));


	sprite_enemigo->changeAnimation(0);
	sprite_enemigo_left->changeAnimation(0);
}

void Boss2::update(int deltaTime)
{

	sprite_enemigo->update(deltaTime);
	sprite_enemigo_left->update(deltaTime);



	if (sprite_enemigo_left->animation() == 7 || sprite_enemigo->animation() == 7) deltaTimeDeath += deltaTime;

	else if (sprite_enemigo_left->animation() == 5 || sprite_enemigo->animation() == 5) hitTime += deltaTime;

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


	if (hitTime > 500 && sprite_enemigo->animation() != 6 && sprite_enemigo_left->animation() != 6 && !sprite_enemigo_left->animation() != 7 && !sprite_enemigo->animation() != 7) {
		if (sprite_enemigo->animation() != 0 || sprite_enemigo_left->animation() != 0) {
			sprite_enemigo->changeAnimation(0);
			sprite_enemigo_left->changeAnimation(0);
			hitTime = 0;
			mciSendString(TEXT("stop sounds/SOUND/puñetazos.mp3"), NULL, 0, NULL);
			mciSendString(TEXT("stop sounds/SOUND/patada.mp3"), NULL, 0, NULL);
		}
	}

	if (movimiento == 0 && sprite_enemigo->animation() == 7 && deltaTimeDeath >= 2400) {
		muerto = true;
	}

	else if (movimiento == 1 && sprite_enemigo_left->animation() == 7 && deltaTimeDeath >= 2400) {
		muerto = true;
	}

	if (sprite_enemigo->animation() == 7 && movimiento == 0 && !muerto) {
		posPlayer.x -= 1;
		//posPlayer.y += 0.1f;
	}

	if (sprite_enemigo_left->animation() == 7 && movimiento == 1 && !muerto) {
		posPlayer.x += 1;
		//posPlayer.y += 0.1f;
	}

	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_enemigo_left->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

void Boss2::render()
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

void Boss2::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
}

void Boss2::recibirPuñetazoIzquierda() {
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
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}
void Boss2::recibirPatadaIzquierda() {
	if (vida > 0 && sprite_enemigo_left->animation() != 6 && (sprite_enemigo_left->animation() != 7)) {
		movimiento = 1;
		if (golpe == 0) sprite_enemigo_left->changeAnimation(5);
		hitTime = 0;
		if (golpe == 0) {
			//mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 15;
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
void Boss2::recibirPuñetazoDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 6 && (sprite_enemigo->animation() != 7)) {
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
	if (vida <= 0 && (sprite_enemigo->animation() != 7) && (sprite_enemigo_left->animation() != 7)) {
		mciSendString(TEXT("stop sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/muerte_enemigo1.mp3"), NULL, 0, NULL);
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}

}
void Boss2::recibirPatadaDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 6 && sprite_enemigo->animation() != 7) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 5) sprite_enemigo->changeAnimation(5);
		hitTime = 0;
		if (golpe == 0) {
			mciSendString(TEXT("play sounds/SOUND/Punch.mp3 "), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
			vida -= 15;
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

void Boss2::recibirPuñetazoArribaDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 6 && (sprite_enemigo->animation() != 7)) {
		movimiento = 0;
		if (sprite_enemigo->animation() != 6) sprite_enemigo->changeAnimation(6);
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
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}

void Boss2::recibirPuñetazoArribaIzquierda() {
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



bool Boss2::isDying() {
	if ((sprite_enemigo->animation() == 7 || sprite_enemigo_left->animation() == 7) && vida <= 0) {
		return true;
	}
	return false;
}
bool Boss2::isDeath() {
	if ((sprite_enemigo->animation() == 7 || sprite_enemigo_left->animation() == 7) && deltaTimeDeath > 2400 & vida <= 0) {
		return true;
	}
	return false;
}

bool Boss2::isCompletlyDeath() {
	if ((sprite_enemigo->animation() == 7 || sprite_enemigo_left->animation() == 7) && deltaTimeDeath > 2400) return true;
	return false;
}

void Boss2::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::vec2 Boss2::getPosition()
{
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
}

void Boss2::free() {
	sprite_enemigo->free();
	sprite_enemigo_left->free();
}


void Boss2::atacarPuñetazosDerecha() {
	if (sprite_enemigo->animation() != 2 && sprite_enemigo->animation() != 7 && sprite_enemigo->animation() != 6 && vida > 0) {
		sprite_enemigo->changeAnimation(2);
		movimiento = 0;
		mciSendString(TEXT("play sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("play sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
	}
}
void Boss2::atacarPuñetadosIzquierda() {
	if (sprite_enemigo_left->animation() != 2 && sprite_enemigo_left->animation() != 7 && sprite_enemigo_left->animation() != 6 && vida > 0) {
		sprite_enemigo_left->changeAnimation(2);
		movimiento = 1;
		mciSendString(TEXT("play sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("play sounds/SOUND/Punch.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/Punch.mp3 volume to 94"), NULL, 0, NULL);
	}
}

bool Boss2::isPunchingRight() {
	if (sprite_enemigo->animation() == 2 && movimiento == 0) return true;
	return false;
}

bool Boss2::isPunchingLeft() {
	if (sprite_enemigo_left->animation() == 2 && movimiento == 1) return true;
	return false;
}

void Boss2::turnToWalk() {
	if (sprite_enemigo->animation() == 2 && movimiento == 0 && !sprite_enemigo->isFinalized()) sprite_enemigo->changeAnimation(0);
	if (sprite_enemigo_left->animation() == 2 && movimiento == 1 && !sprite_enemigo_left->isFinalized()) sprite_enemigo_left->changeAnimation(0);
}

bool Boss2::isRecuperando() {
	if (sprite_enemigo_left->animation() == 6 && movimiento == 1) return true;
	else if (sprite_enemigo->animation() == 6 && movimiento == 0) return true;
	if (sprite_enemigo_left->animation() == 5 && movimiento == 1 && hitTime < 500) return true;
	else if (sprite_enemigo->animation() == 5 && movimiento == 0 && hitTime < 500) return true;
	return false;
}

bool Boss2::isRecibiendo() {
	if (sprite_enemigo_left->animation() == 5 && movimiento == 1 && hitTime < 500) return true;
	else if (sprite_enemigo->animation() == 5 && movimiento == 0 && hitTime < 500) return true;
	return false;
}

void Boss2::setGolpesto0() {
	golpe = 0;
}

void Boss2::moverse(float xP, float yP) {
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

bool Boss2::estaCerca(float xP, float yP)
{
	return ((abs(xP - posPlayer.x) < 200) && (abs(yP - posPlayer.y) < 200) && (abs(yP - posPlayer.y) >= 3) && (abs(xP - posPlayer.x) >= 3));
}

int Boss2::posPlx(float xP)
{
	if (xP <= posPlayer.x) {
		return 0;
	}
	else return 1;
}

int Boss2::posPly(float yP)
{
	if ((yP - 45) <= posPlayer.y) {
		return 0;
	}
	else return 1;
}