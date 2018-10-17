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
	movimiento = 0;
	spritesheet_enemigo.loadFromFile("images/Enemigo1/sprite_enemigo1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_enemigo = Sprite::createSprite(glm::ivec2(100, 110), glm::vec2(0.0196078431, 1), &spritesheet_enemigo, &shaderProgram);
	sprite_enemigo->setNumberAnimations(8);

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
	


	sprite_enemigo->changeAnimation(0);
	
	//tileMapDispl = tileMapPos;
}

void Enemigo1::update(int deltaTime)
{

	sprite_enemigo->update(deltaTime);

	if (Game::instance().getKey('q')) {
		sprite_enemigo->changeAnimation(0);
	}
	else if (Game::instance().getKey('w')) {
		sprite_enemigo->changeAnimation(1);
	}
	else if (Game::instance().getKey('e')) {
		sprite_enemigo->changeAnimation(2);
	}
	else if (Game::instance().getKey('2')) {
		sprite_enemigo->changeAnimation(3);
	}
	else if (Game::instance().getKey('3')) {
		sprite_enemigo->changeAnimation(4);
	}
	else if (Game::instance().getKey('4')) {
		sprite_enemigo->changeAnimation(5);
	}
	else if (Game::instance().getKey('5')) {
		sprite_enemigo->changeAnimation(6);
	}
	else if (Game::instance().getKey('6')) {
		sprite_enemigo->changeAnimation(7);
	}

	if (sprite_enemigo->animation() == 7) posPlayer.x -= 0.5;
	//if (sprite_enemigo->)


	sprite_enemigo->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
}

void Enemigo1::render()
{
	switch (movimiento)
	{
	case 0:
		sprite_enemigo->render();
		break;
	case 1:
		sprite_enemigo_right->render();
		break;
	}
}

void Enemigo1::setTileMap(TileMap *tileMap)
{
	//map = tileMap;
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
