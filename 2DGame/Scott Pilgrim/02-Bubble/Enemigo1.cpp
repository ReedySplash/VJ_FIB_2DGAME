#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemigo1.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define FALL_STEP 4

enum EnumEnemy
{
	STAND_LEFT, STAND_RIGHT, WALK_LEFT, WALK_RIGHT, RUN_LEFT, RUN_RIGHT, PUNCH_LEFT, PUNCH_RIGHT, KICK_LEFT, KICK_RIGHT, RECIBIR_LEFT, RECIBIR_RIGHT, RECIBIR_LEFT2, RECIBIR_RIGHT2, MORIR_LEFT, MORIR_RIGHT
};


void Enemigo1::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	mapShader = shaderProgram;
	vida = 100;
	movimiento = 1;
	spritesheet_enemigo.loadFromFile("images/Enemigo1/sprite_enemigo1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo = Sprite::createSprite(glm::ivec2(100, 110), glm::vec2(0.0196078431, 1), &spritesheet_enemigo, &shaderProgram);
	sprite_enemigo->setNumberAnimations(9);

	sprite_enemigo->setAnimationSpeed(0, 8);
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0196078431 * 0, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0196078431 * 1, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0196078431 * 2, 0.f));
	sprite_enemigo->addKeyframe(0, glm::vec2(0.0196078431 * 3, 0.f));

	sprite_enemigo->setAnimationSpeed(1, 8);
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 4, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 5, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 6, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 7, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 8, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 9, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 10, 0.f));
	sprite_enemigo->addKeyframe(1, glm::vec2(0.0196078431 * 11, 0.f));

	sprite_enemigo->setAnimationSpeed(2, 8);
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 12, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 13, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 14, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 15, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 16, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 17, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 18, 0.f));
	sprite_enemigo->addKeyframe(2, glm::vec2(0.0196078431 * 19, 0.f));

	sprite_enemigo->setAnimationSpeed(3, 8);
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0196078431 * 20, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0196078431 * 21, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0196078431 * 22, 0.f));
	sprite_enemigo->addKeyframe(3, glm::vec2(0.0196078431 * 23, 0.f));

	sprite_enemigo->setAnimationSpeed(4, 8);
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0196078431 * 24, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0196078431 * 25, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0196078431 * 26, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0196078431 * 27, 0.f));
	sprite_enemigo->addKeyframe(4, glm::vec2(0.0196078431 * 28, 0.f));

	sprite_enemigo->setAnimationSpeed(5, 6);
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0196078431 * 29, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0196078431 * 30, 0.f));
	sprite_enemigo->addKeyframe(5, glm::vec2(0.0196078431 * 31, 0.f));

	sprite_enemigo->setAnimationSpeed(6, 6);
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0196078431 * 32, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0196078431 * 33, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0196078431 * 34, 0.f));
	sprite_enemigo->addKeyframe(6, glm::vec2(0.0196078431 * 35, 0.f));

	sprite_enemigo->setAnimationSpeed(7, 7);
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 36, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 37, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 38, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 39, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 40, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 41, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 42, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 43, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 44, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 45, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 46, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 47, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 48, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 49, 0.f));
	sprite_enemigo->addKeyframe(7, glm::vec2(0.0196078431 * 50, 0.f));

	sprite_enemigo->setAnimationSpeed(8, 7);
	sprite_enemigo->addKeyframe(8, glm::vec2(0.0196078431 * 50, 0.f));



	spritesheet_enemigo_left.loadFromFile("images/Enemigo1/sprite_enemigo1_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo_left = Sprite::createSprite(glm::ivec2(100, 110), glm::vec2(0.0196078431, 1), &spritesheet_enemigo_left, &shaderProgram);
	sprite_enemigo_left->setNumberAnimations(9);

	sprite_enemigo_left->setAnimationSpeed(0, 8);
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0196078431 * 50, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0196078431 * 49, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0196078431 * 48, 0.f));
	sprite_enemigo_left->addKeyframe(0, glm::vec2(0.0196078431 * 47, 0.f));

	sprite_enemigo_left->setAnimationSpeed(1, 8);
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 46, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 45, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 44, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 43, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 42, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 41, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 40, 0.f));
	sprite_enemigo_left->addKeyframe(1, glm::vec2(0.0196078431 * 39, 0.f));

	sprite_enemigo_left->setAnimationSpeed(2, 8);
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 38, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 37, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 36, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 35, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 34, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 33, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 32, 0.f));
	sprite_enemigo_left->addKeyframe(2, glm::vec2(0.0196078431 * 31, 0.f));

	sprite_enemigo_left->setAnimationSpeed(3, 8);
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0196078431 * 30, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0196078431 * 29, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0196078431 * 28, 0.f));
	sprite_enemigo_left->addKeyframe(3, glm::vec2(0.0196078431 * 27, 0.f));

	sprite_enemigo_left->setAnimationSpeed(4, 8);
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0196078431 * 26, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0196078431 * 25, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0196078431 * 24, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0196078431 * 23, 0.f));
	sprite_enemigo_left->addKeyframe(4, glm::vec2(0.0196078431 * 22, 0.f));

	sprite_enemigo_left->setAnimationSpeed(5, 6);
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0196078431 * 21, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0196078431 * 20, 0.f));
	sprite_enemigo_left->addKeyframe(5, glm::vec2(0.0196078431 * 19, 0.f));

	sprite_enemigo_left->setAnimationSpeed(6, 6);
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0196078431 * 18, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0196078431 * 17, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0196078431 * 16, 0.f));
	sprite_enemigo_left->addKeyframe(6, glm::vec2(0.0196078431 * 15, 0.f));

	sprite_enemigo_left->setAnimationSpeed(7, 7);
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 14, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 13, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 12, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 11, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 10, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 9, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 8, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 7, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 6, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 5, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 4, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 3, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 2, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 1, 0.f));
	sprite_enemigo_left->addKeyframe(7, glm::vec2(0.0196078431 * 0, 0.f));


	sprite_enemigo_left->setAnimationSpeed(8, 7);
	sprite_enemigo_left->addKeyframe(8, glm::vec2(0.0196078431 * 0, 0.f));




	sprite_enemigo->changeAnimation(0);
	sprite_enemigo_left->changeAnimation(0);

	//tileMapDispl = tileMapPos;
}

void Enemigo1::update(int deltaTime)
{

	sprite_enemigo->update(deltaTime);
	sprite_enemigo_left->update(deltaTime);


	if (sprite_enemigo_left->animation() == 7 || sprite_enemigo->animation() == 7 || sprite_enemigo->animation() == 8) deltaTimeDeath += deltaTime;

	else if (sprite_enemigo_left->animation() == 5 || sprite_enemigo_left->animation() == 6 || sprite_enemigo->animation() == 6 || sprite_enemigo->animation() == 5) hitTime += deltaTime;

	if (hitTime > 500 && sprite_enemigo->animation() != 8 && sprite_enemigo_left->animation() != 8 && sprite_enemigo->animation() != 7 && sprite_enemigo_left->animation() != 7) {
		if (sprite_enemigo->animation() != 0 || sprite_enemigo_left->animation() != 0) {
			sprite_enemigo->changeAnimation(0);
			sprite_enemigo_left->changeAnimation(0);
		}
	}

	if (movimiento == 0 && sprite_enemigo->animation() == 7 && deltaTimeDeath >= 2000) {
		sprite_enemigo->changeAnimation(8);
	}

	else if (movimiento == 1 && sprite_enemigo_left->animation() == 7 && deltaTimeDeath >= 2000) {
		sprite_enemigo_left->changeAnimation(8);
	}

	if (sprite_enemigo->animation() == 8 || sprite_enemigo_left->animation() == 8) timeAfterDeath += deltaTime;

	/*else if (Game::instance().getKey('1')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(0);
	}
	else if (Game::instance().getKey('2')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(1);
	}
	else if (Game::instance().getKey('3')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(2);
	}
	else if (Game::instance().getKey('4')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(3);
	}
	else if (Game::instance().getKey('5')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(4);
	}
	else if (Game::instance().getKey('6')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(5);
	}
	else if (Game::instance().getKey('7')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(6);
	}
	else if (Game::instance().getKey('8')) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}

	else if (Game::instance().getKey('y')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(0);
	}
	else if (Game::instance().getKey('u')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(1);
	}
	else if (Game::instance().getKey('i')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(2);
	}
	else if (Game::instance().getKey('o')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(3);
	}
	else if (Game::instance().getKey('p')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(4);
	}
	else if (Game::instance().getKey('h')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(5);
	}
	else if (Game::instance().getKey('j')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(6);
	}
	else if (Game::instance().getKey('k')) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}*/


	if (sprite_enemigo->animation() == 7 && movimiento == 0) {
		posPlayer.x -= 1;
		posPlayer.y += 0.1f;
	}

	if (sprite_enemigo_left->animation() == 7 && movimiento == 1) {
		posPlayer.x += 1;
		posPlayer.y += 0.1f;
	}

	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	sprite_enemigo_left->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

void Enemigo1::render()
{
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

void Enemigo1::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
}

void Enemigo1::recibirPuñetazoIzquierda() {
	if (vida > 0 && sprite_enemigo_left->animation() != 7 && (sprite_enemigo_left->animation() != 8)) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(5);
		hitTime = 0;
		vida -= 5;
	}
	if (vida <= 0 && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 8)) {
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}
void Enemigo1::recibirPatadaIzquierda() {
	if (vida > 0 && sprite_enemigo_left->animation() != 7 && (sprite_enemigo_left->animation() != 8)) {
		movimiento = 1;
		sprite_enemigo_left->changeAnimation(6);
		hitTime = 0;
		vida -= 10;
	}
	if (vida <= 0 && (sprite_enemigo_left->animation() != 8) && (sprite_enemigo->animation() != 8)) {
		sprite_enemigo_left->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}
void Enemigo1::recibirPuñetazoDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 7 && (sprite_enemigo->animation() != 8)) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(5);
		hitTime = 0;
		vida -= 5;
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 8) && (sprite_enemigo_left->animation() != 8)) {
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}
void Enemigo1::recibirPatadaDerecha() {
	if (vida > 0 && sprite_enemigo->animation() != 7 && (sprite_enemigo->animation() != 8)) {
		movimiento = 0;
		sprite_enemigo->changeAnimation(6);
		hitTime = 0;
		vida -= 10;
	}
	if (vida <= 0 && (sprite_enemigo->animation() != 8) && (sprite_enemigo_left->animation() != 8)) {
		sprite_enemigo->changeAnimation(7);
		deltaTimeDeath = 0;
	}
}

bool Enemigo1::isDeath() {
	if ((sprite_enemigo->animation() == 8 || sprite_enemigo_left->animation() == 8) && timeAfterDeath > 1000) {
		return true;
	}
	return false;
}

void Enemigo1::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

glm::vec2 Enemigo1::getPosition()
{
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
}

void Enemigo1::free() {
	sprite_enemigo->free();
	sprite_enemigo_left->free();
}

