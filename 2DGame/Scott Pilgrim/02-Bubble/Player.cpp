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


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{	
	movimiento = 0;
	bJumping = false;
	spritesheet.loadFromFile("images/Scott quieto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(38.625, 59), glm::vec2(0.125, 1), &spritesheet, &shaderProgram);
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

	spritesheet_standLeft.loadFromFile("images/Scott quieto left.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_standLeft = Sprite::createSprite(glm::ivec2(38.625, 59), glm::vec2(0.125, 1), &spritesheet_standLeft, &shaderProgram);
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


	spritesheet_caminando.loadFromFile("images/0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_caminando = Sprite::createSprite(glm::ivec2(36.833333333, 63), glm::vec2(0.1666666667, 1), &spritesheet_caminando, &shaderProgram);
	sprite_caminando->setNumberAnimations(4);


		sprite_caminando->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666666667, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333333333, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.6777777777, 0.f));
		sprite_caminando->addKeyframe(MOVE_RIGHT, glm::vec2(0.83333333333, 0.f));

	spritesheet_caminando_izq.loadFromFile("images/0_izq.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite_caminando_izq = Sprite::createSprite(glm::ivec2(36.83333333, 63), glm::vec2(0.1666666667, 1), &spritesheet_caminando_izq, &shaderProgram);
		sprite_caminando_izq->setNumberAnimations(4);


		sprite_caminando_izq->setAnimationSpeed(MOVE_LEFT, 8);
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.833333333, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.6777777777, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.3333333333, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.1666666667, 0.f));
		sprite_caminando_izq->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));



			
	sprite->changeAnimation(STAND_RIGHT);
	sprite_standLeft->changeAnimation(STAND_LEFT);
	sprite_caminando->changeAnimation(MOVE_RIGHT);
	sprite_caminando_izq->changeAnimation(MOVE_LEFT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite_caminando->update(deltaTime);
	sprite_standLeft->update(deltaTime);
	sprite_caminando_izq->update(deltaTime);
	
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		movimiento = 2;
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(36.83333333, 61)))
		{
			posPlayer.x += 2;
			movimiento = 0;
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{	
		movimiento = 3;
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(36.83333333, 61)))
		{
			movimiento = 1;
			posPlayer.x -= 2;
		}
	}
	else
	{	
		if (movimiento == 2)
			movimiento = 0;
		else if(movimiento == 3)
			movimiento = 1;
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(36.83333333, 61), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(36.83333333, 63), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));


}

void Player::render()
{
	if (movimiento == 0) sprite_standLeft->render();
	else if (movimiento == 1) sprite->render();
	else if (movimiento == 2) sprite_caminando_izq->render();
	else if (movimiento == 3) sprite_caminando->render();

}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_standLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite_caminando_izq->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




