#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level1.h"
#include "Game.h"
#include <string>


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 50
#define INIT_PLAYER_Y_TILES 150


Level1::Level1()
{
	player = NULL;
}

Level1::~Level1()
{
	if (player != NULL)
		delete player;

	for (int i = 0; i<3; i++)
		if (texQuad[i] != NULL)
			delete texQuad[i];
}


void Level1::init(bool music, int pers)
{
	if(music) {
		mciSendString(TEXT("stop sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/Level1.mp3 repeat"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/Level1.mp3 volume to 94"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("stop sounds/SOUND/level1.mp3"), NULL, 0, NULL);
	}
	musica = music;
	currentTime = 0.0f;
	initShaders();

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 texCoords[2];
	texCoords[0] = glm::vec2(0, 0); texCoords[1] = glm::vec2(1, 1);
	puntuacion = 0;
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, simpleTexProgram);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texQuad[3] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/Levels/level1new.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	texs[1].loadFromFile("images/sombra.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].setMagFilter(GL_NEAREST);
	texs[2].loadFromFile("images/GameOver.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[2].setMagFilter(GL_NEAREST);
	texs[3].loadFromFile("images/LevelFinalized.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[3].setMagFilter(GL_NEAREST);
	personaje = pers;
	hud.init(1, texProgram, simpleTexProgram);
	if (!text.init("fonts/pixeldu.ttf"))
		cout << "Could not load font!!!" << endl;

	for (int i = 0; i < 10; ++i) {
		muertos[i] = false;
	}

	//Init jugador, depende del elegido
	if (personaje == 0) {
		//Init player
		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram, 1);
		player->setPosition(glm::vec2(65, 260));
		//player->setTileMap(map);
	}

	else if (personaje == 1) {
		kim = new Kim();
		kim->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram, 1);
		kim->setPosition(glm::vec2(65, 260));
	}

	else if (personaje == 2) {
		ramona = new Ramona();
		ramona->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram, 1);
		ramona->setPosition(glm::vec2(65, 260));
	}

	//Init Enemigos
	for (int i = 0; i < 3; ++i) {
		enemigo1[i] = new Enemigo1();
		enemigo1[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
		enemigo1[i]->setPosition(glm::vec2((i+1)*150, 260));
		enemigo2[i] = new Enemigo2();
		enemigo2[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
		enemigo2[i]->setPosition(glm::vec2((i + 1) * 150 + 800, 260));
		enemigo3[i] = new Enemigo3();
		enemigo3[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
		enemigo3[i]->setPosition(glm::vec2((i + 1) *150 + 1700, 260));
	}
	boss = new Boss1();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
	boss->setPosition(glm::vec2(3250, 220));


	x = 0.f;
	projection = glm::ortho(0.f, 50.f, float(SCREEN_HEIGHT - 1), 0.f);

}

void Level1::update(int deltaTime)
{
	currentTime += deltaTime;
	bool isWalking, isRunning;
	if (personaje == 0) {
		player->update(deltaTime);
		pos = player->getPosition();
		isWalking = player->isWalking();
		isRunning = player->isRunning();
	}
	else if (personaje == 1) {
		kim->update(deltaTime);
		pos = kim->getPosition();
		isWalking = kim->isWalking();
		isRunning = kim->isRunning();
	}

	else if (personaje == 2) {
		ramona->update(deltaTime);
		pos = ramona->getPosition();
		isWalking = ramona->isWalking();
		isRunning = ramona->isRunning();
	}
	
	if (x < 212) {
		if (pos.x >= 380 && isWalking) {
			x += 0.2f;
			projection = glm::ortho(min(max(0, 0 + x), 0 + 218), min(max(50, 50 + x), 50 + 218), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 3; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose1 = enemigo1[i]->getPosition();
					if (x < 218) pose1.x -= 2.57f;
					enemigo1[i]->setPosition(pose1);
				}
				if (!enemigo2[i]->isCompletlyDeath()) {
					glm::vec2 pose2 = enemigo2[i]->getPosition();
					if (x < 218) pose2.x -= 2.57f;
					enemigo2[i]->setPosition(pose2);
				}
				if (!enemigo3[i]->isCompletlyDeath()) {
					glm::vec2 pose3 = enemigo3[i]->getPosition();
					if (x < 218) pose3.x -= 2.57f;
					enemigo3[i]->setPosition(pose3);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x < 218) pose.x -= 2.57f;
			boss->setPosition(pose);

		}
		else if (pos.x <= 200 && isWalking) {
			x -= 0.2f;
			projection = glm::ortho(min(max(0, 0 + x), 0 + 218), min(max(50, 50 + x), 50 + 218), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 3; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose1 = enemigo1[i]->getPosition();
					if (x > 0) pose1.x += 2.57f;
					enemigo1[i]->setPosition(pose1);
				}
				if (!enemigo2[i]->isCompletlyDeath()) {
					glm::vec2 pose2 = enemigo2[i]->getPosition();
					if (x > 0) pose2.x += 2.57f;
					enemigo2[i]->setPosition(pose2);
				}
				if (!enemigo3[i]->isCompletlyDeath()) {
					glm::vec2 pose3 = enemigo3[i]->getPosition();
					if (x > 0) pose3.x += 2.57f;
					enemigo3[i]->setPosition(pose3);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x > 0) pose.x += 2.57f;
			boss->setPosition(pose);
		}
		else if (pos.x >= 380 && isRunning) {
			x += 0.35f;
			projection = glm::ortho(min(max(0, 0 + x), 0 + 218), min(max(50, 50 + x), 50 + 218), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 3; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose1 = enemigo1[i]->getPosition();
					if (x < 218) pose1.x -= 2.6f*1.725f;
					enemigo1[i]->setPosition(pose1);
				}
				if (!enemigo2[i]->isCompletlyDeath()) {
					glm::vec2 pose2 = enemigo2[i]->getPosition();
					if (x < 218) pose2.x -= 2.6f*1.725f;
					enemigo2[i]->setPosition(pose2);
				}
				if (!enemigo3[i]->isCompletlyDeath()) {
					glm::vec2 pose3 = enemigo3[i]->getPosition();
					if (x < 218) pose3.x -= 2.6f*1.725f;
					enemigo3[i]->setPosition(pose3);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x < 218) pose.x -= 2.6f*1.725f;
			boss->setPosition(pose);
		}
		else if (pos.x <= 200 && isRunning) {
			x -= 0.35f;
			projection = glm::ortho(min(max(0, 0 + x), 0 + 218), min(max(50, 50 + x), 50 + 218), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 3; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose1 = enemigo1[i]->getPosition();
					if (x > 0) pose1.x += 2.6f*1.725f;
					enemigo1[i]->setPosition(pose1);
				}
				if (!enemigo2[i]->isCompletlyDeath()) {
					glm::vec2 pose2 = enemigo2[i]->getPosition();
					if (x > 0) pose2.x += 2.6f*1.725f;
					enemigo2[i]->setPosition(pose2);
				}
				if (!enemigo3[i]->isCompletlyDeath()) {
					glm::vec2 pose3 = enemigo3[i]->getPosition();
					if (x > 0) pose3.x += 2.6f*1.725f;
					enemigo3[i]->setPosition(pose3);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x > 0) pose.x += 2.6f*1.725f;
			boss->setPosition(pose);
		}
		if (x <= 0) x = 0.f;
		else if (x > 218) x = 218.f;

		for (int i = 0; i < 3; ++i) {
			comprobarLucha(i, pos, 1);
			comprobarLucha(i, pos, 2);
			comprobarLucha(i, pos, 3);
			if (!enemigo1[i]->isDying()) comprobarAtaqueEnemigo(i, pos, 1);
			if (!enemigo2[i]->isDying()) comprobarAtaqueEnemigo(i, pos, 2);
			if (!enemigo3[i]->isDying()) comprobarAtaqueEnemigo(i, pos, 3);
			if (enemigo1[i]->isDying()) atacando1[i] = false;
			if (enemigo2[i]->isDying()) atacando2[i] = false;
			if (enemigo3[i]->isDying()) atacando3[i] = false;
			enemigo1[i]->update(deltaTime);
			enemigo2[i]->update(deltaTime);
			enemigo3[i]->update(deltaTime);
			if (!enemigo1[i]->isPunchingLeft() && !enemigo1[i]->isPunchingRight() && !enemigo1[i]->isRecuperando()) enemigo1[i]->moverse(pos.x, pos.y);
			if (!enemigo2[i]->isPunchingLeft() && !enemigo2[i]->isPunchingRight() && !enemigo2[i]->isRecuperando()) enemigo2[i]->moverse(pos.x, pos.y);
			if (enemigo1[i]->isCompletlyDeath()) muertos[i] = true;
			if (enemigo2[i]->isCompletlyDeath()) muertos[i+3] = true;
			if (enemigo3[i]->isCompletlyDeath()) muertos[i+6] = true;
		}
	}

	else if (x != 213 ) {
		x = 213;
		projection = glm::ortho(float(x), float(x+50), float(SCREEN_HEIGHT - 1), 0.f);
		mciSendString(TEXT("stop sounds/SOUND/level1.mp3"), NULL, 0, NULL);
		if (musica) {
			mciSendString(TEXT("play sounds/SOUND/boss.mp3 repeat"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/boss.mp3 volume to 98"), NULL, 0, NULL);
		}
	}
	yplayer = pos.y;
	
	if (x == 213 && !atacando_boss && !boss->isRecuperando()) boss->moverse(pos.x, pos.y);
	comprobarLuchaBoss(pos);
	comprobarAtaqueBoss(pos);
	boss->update(deltaTime);

	if (personaje == 0) hud.changeLife(player->getVida());
	else if (personaje == 1) hud.changeLife(kim->getVida());
	else hud.changeLife(ramona->getVida());
	hud.update(deltaTime);

	if (boss->isCompletlyDeath()) {
		muertos[9] = true;
		if (musica) {
			mciSendString(TEXT("stop sounds/SOUND/boss.mp3"), NULL, 0, NULL);
			mciSendString(TEXT("play sounds/SOUND/VictoryTheme.mp3 repeat"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/VictoryTheme.mp3 volume to 98"), NULL, 0, NULL);
		}
	}
	puntuacion = 0;
	for (int i = 0; i < 9; ++i) {
		if (muertos[i]) puntuacion += 10;
	}
	if (muertos[9]) puntuacion += 110;
}

void Level1::render()
{
	glm::mat4 modelview;

	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);
	//map->render();

	texProgram.use();
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT - 1), 0.f));
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	glm::mat4 modelview2;
	bool jumping;
	//comprobamos si salta, si no lo hace, nos guardamos su y por si lo hace
	if (personaje == 0) {
		jumping = player->isJumping();
		if (!jumping && !player->isRecuperando() && player->getVida() > 0) y = pos.y;
		if (jumping) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
		else if (player->isRecuperando()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y+80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}

		else if (player->getVida() <= 0) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}

		else {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, pos.y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
	}
	else if (personaje == 1) {
		jumping = kim->isJumping();
		if (!jumping && !kim->isRecuperando() && kim->getVida() > 0) y = pos.y;
		if (jumping) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
		else if (kim->isRecuperando()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y+80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}

		else if (kim->getVida() <= 0) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}

		else {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, pos.y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
	}

	else if (personaje == 2) {
		jumping = ramona->isJumping();
		if (!jumping && !ramona->isRecuperando() && ramona->getVida() > 0) y = pos.y;
		if (jumping) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
		else if (ramona->isRecuperando()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}

		else if (ramona->getVida() <= 0) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}

		else {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, pos.y + 80, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
	}
	//else if (personaje == 2) ramona->render();

	//renderizamos sombras enemigas
	int i;
	for (i = 0; i < 3; ++i) {
		if (!enemigo1[i]->isCompletlyDeath() && !enemigo1[i]->isDying()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(enemigo1[i]->getPosition().x + 18, enemigo1[i]->getPosition().y + 120, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.10f, 0.08f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
		else if (!enemigo1[i]->isCompletlyDeath() && enemigo1[i]->isDying()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(enemigo1[i]->getPosition().x + 20, enemigo1[i]->getPosition().y + 90, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.10f, 0.08f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
		if (!enemigo2[i]->isCompletlyDeath() && !enemigo2[i]->isDying()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(enemigo2[i]->getPosition().x + 18, enemigo2[i]->getPosition().y + 130, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.10f, 0.08f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
		else if (!enemigo2[i]->isCompletlyDeath() && enemigo2[i]->isDying()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(enemigo2[i]->getPosition().x + 20, enemigo2[i]->getPosition().y + 95, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.10f, 0.08f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
		if (!enemigo3[i]->isCompletlyDeath()) {
			modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
			modelview2 = glm::translate(modelview2, glm::vec3(enemigo3[i]->getPosition().x + 35, enemigo3[i]->getPosition().y + 120, 0.f));
			modelview2 = glm::scale(modelview2, glm::vec3(0.10f, 0.08f, 0.f));
			texProgram.setUniformMatrix4f("modelview", modelview2);
			texQuad[1]->render(texs[1]);
		}
	}

	//sombra boss
	
	if ((!boss->isDying() && !boss->isCompletlyDeath() && !boss->isRecuperando()) || (!boss->isDying() && !boss->isCompletlyDeath() && boss->isRecibiendo())) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(boss->getPosition().x + 20, boss->getPosition().y + 125, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.06f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	else if (boss->isRecuperando() && !boss->isRecibiendo()) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(boss->getPosition().x + 20, boss->getPosition().y + 110, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.06f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);

	for (i = 0; i < 3; ++i) {
		if (enemigo1[i]->getPosition().y + 40 <= y && !enemigo1[i]->isCompletlyDeath() && !enemigo1[i]->isDeath() && !enemigo1[i]->isDying()) {
			enemigo1[i]->render();
		}
		else if (enemigo1[i]->getPosition().y <= y - 10 && !enemigo1[i]->isCompletlyDeath() && (enemigo1[i]->isDeath() || enemigo1[i]->isDying())) {
			enemigo1[i]->render();
		}
		if (enemigo2[i]->getPosition().y + 40 <= y && !enemigo2[i]->isCompletlyDeath() && !enemigo2[i]->isDeath() && !enemigo2[i]->isDying()) {
			enemigo2[i]->render();
		}
		else if (enemigo2[i]->getPosition().y <= y - 10 && !enemigo2[i]->isCompletlyDeath() && (enemigo2[i]->isDeath() || enemigo2[i]->isDying())) {
			enemigo2[i]->render();
		}
		if (enemigo3[i]->getPosition().y + 40 <= y && !enemigo3[i]->isCompletlyDeath() && !enemigo3[i]->isDeath() && !enemigo3[i]->isDying()) {
			enemigo3[i]->render();
		}
		else if (enemigo3[i]->getPosition().y <= y - 10 && !enemigo3[i]->isCompletlyDeath() && (enemigo3[i]->isDeath() || enemigo3[i]->isDying())) {
			enemigo3[i]->render();
		}
	}
	if (boss->getPosition().y < y-20) boss->render();
	if (personaje == 0) player->render();
	else if (personaje == 1) kim->render();
	else if (personaje == 2) ramona->render();
	
	for (i = 0; i < 3; ++i) {
		if (enemigo1[i]->getPosition().y + 40 > y && !enemigo1[i]->isCompletlyDeath() && !enemigo1[i]->isDeath() && !enemigo1[i]->isDying()) enemigo1[i]->render();
		else if (enemigo1[i]->getPosition().y > y - 10 && !enemigo1[i]->isCompletlyDeath() && (enemigo1[i]->isDeath() || enemigo1[i]->isDying())) enemigo1[i]->render();
		if (enemigo2[i]->getPosition().y + 40 > y && !enemigo2[i]->isCompletlyDeath() && !enemigo2[i]->isDeath() && !enemigo2[i]->isDying()) enemigo2[i]->render();
		else if (enemigo2[i]->getPosition().y > y - 10 && !enemigo2[i]->isCompletlyDeath() && (enemigo2[i]->isDeath() || enemigo2[i]->isDying())) enemigo2[i]->render();
		if (enemigo3[i]->getPosition().y + 40 > y && !enemigo3[i]->isCompletlyDeath() && !enemigo3[i]->isDeath() && !enemigo3[i]->isDying()) enemigo3[i]->render();
		else if (enemigo3[i]->getPosition().y > y - 10 && !enemigo3[i]->isCompletlyDeath() && (enemigo3[i]->isDeath() || enemigo3[i]->isDying())) enemigo3[i]->render();
	}
	
	if (boss->getPosition().y >= y-20) boss->render();
	hud.render();

	modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	modelview2 = glm::translate(modelview2, glm::vec3(60.f, 50.f, 0.f));
	modelview2 = glm::scale(modelview2, glm::vec3(0.8f, 0.8f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview2);
	if (personaje == 0 && player->isDead()) texQuad[2]->render(texs[2]);
	else if (personaje == 1 && kim->isDead()) texQuad[2]->render(texs[2]);
	else if (personaje == 2 && ramona->isDead()) texQuad[2]->render(texs[2]);

	if (boss->isCompletlyDeath()) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(160.f, 100.f, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.5f, 0.3f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[3]->render(texs[3]);
	}

	if(glutGet(GLUT_WINDOW_WIDTH) == 1280)
		text.render("Points: " + std::to_string(puntuacion), glm::vec2(800, 110), 51, glm::vec4(1, 1, 1, 1));
	else if (glutGet(GLUT_WINDOW_WIDTH) == 1920)
		text.render("Points: " + std::to_string(puntuacion), glm::vec2(1300, 150), 65, glm::vec4(1, 1, 1, 1));

}


void Level1::comprobarLucha(int i, glm::vec2 posPlayer, int enemigo) {
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right, isPunching_up_left, isPunching_up_right;
	if (personaje == 0) {
		isPunching_left = player->isPunching_left();
		isPunching_right = player->isPunching_right();
		isKicking_left = player->isKicking_left();
		isKicking_right = player->isKicking_right();
		isPunching_up_left = player->isPunching_up_left();
		isPunching_up_right = player->isPunching_up_right();
	}
	else if (personaje == 1) {
		isPunching_left = kim->isPunching_left();
		isPunching_right = kim->isPunching_right();
		isKicking_left = kim->isKicking_left();
		isKicking_right = kim->isKicking_right();
		isPunching_up_left = kim->isPunching_up_left();
		isPunching_up_right = kim->isPunching_up_right();
	}
	else if (personaje == 2) {
		isPunching_left = ramona->isPunching_left();
		isPunching_right = ramona->isPunching_right();
		isKicking_left = ramona->isKicking_left();
		isKicking_right = ramona->isKicking_right();
		isPunching_up_left = ramona->isPunching_up_left();
		isPunching_up_right = ramona->isPunching_up_right();
	}
	if (enemigo == 1) posEnemy = enemigo1[i]->getPosition();
	if (enemigo == 2) posEnemy = enemigo2[i]->getPosition();
	if (enemigo == 3) posEnemy = enemigo3[i]->getPosition();

	if ((posPlayer.x <= (posEnemy.x + 90) && (posPlayer.x - 30 > posEnemy.x)) && (posPlayer.y >= posEnemy.y + 40  && posPlayer.y <= posEnemy.y + 60)) {
		if (isPunching_left) {
			if (enemigo == 1) enemigo1[i]->recibirPuñetazoDerecha();
			if (enemigo == 2) enemigo2[i]->recibirPuñetazoDerecha();
			if (enemigo == 3) enemigo3[i]->recibirPuñetazoDerecha();
		}
		else if (isKicking_left) {
			if (enemigo == 1) enemigo1[i]->recibirPatadaDerecha();
			if (enemigo == 2) enemigo2[i]->recibirPatadaDerecha();
			if (enemigo == 3) enemigo3[i]->recibirPatadaDerecha();
		}
		else if (isPunching_up_left) {
			if (enemigo == 1) enemigo1[i]->recibirPuñetazoArribaDerecha();
			if (enemigo == 2) enemigo2[i]->recibirPuñetazoArribaDerecha();
			if (enemigo == 3) enemigo3[i]->recibirPuñetazoArribaDerecha();
		}
		else {
			if (enemigo == 1) enemigo1[i]->setGolpesto0();
			if (enemigo == 2) enemigo2[i]->setGolpesto0();
			if (enemigo == 3) enemigo3[i]->setGolpesto0();
		}
	}

	else if ((posPlayer.x >= posEnemy.x - 30 && posPlayer.x < posEnemy.x+20) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 60)) {
		if (isPunching_right) {
			if (enemigo == 1) enemigo1[i]->recibirPuñetazoIzquierda();
			if (enemigo == 2) enemigo2[i]->recibirPuñetazoIzquierda();
			if (enemigo == 3) enemigo3[i]->recibirPuñetazoIzquierda();
		}
		else if (isKicking_right) {
			if (enemigo == 1) enemigo1[i]->recibirPatadaIzquierda();
			if (enemigo == 2) enemigo2[i]->recibirPatadaIzquierda();
			if (enemigo == 3) enemigo3[i]->recibirPatadaIzquierda();
		}
		else if (isPunching_up_right) {
			if (enemigo == 1) enemigo1[i]->recibirPuñetazoArribaIzquierda();
			if (enemigo == 2) enemigo2[i]->recibirPuñetazoArribaIzquierda();
			if (enemigo == 3) enemigo3[i]->recibirPuñetazoArribaIzquierda();
		}
		else {
			if (enemigo == 1) enemigo1[i]->setGolpesto0();
			if (enemigo == 2) enemigo2[i]->setGolpesto0();
			if (enemigo == 3) enemigo3[i]->setGolpesto0();
		}
	}
}

void Level1::comprobarAtaqueEnemigo(int i, glm::vec2 posPlayer, int enemigo) {
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right;
	bool isDead, isRecuperando, isDying;
	int vida_quitada;
	if (enemigo == 1) { isDead = enemigo1[i]->isDeath(); isRecuperando = enemigo1[i]->isRecuperando(); vida_quitada = 3; }
	if (enemigo == 2) { isDead = enemigo2[i]->isDeath(); isRecuperando = enemigo2[i]->isRecuperando(); vida_quitada = 5; }
	if (enemigo == 3) { isDead = enemigo3[i]->isDeath(); isRecuperando = enemigo3[i]->isRecuperando(); vida_quitada = 10; }
	if (!isDead && !isRecuperando) {
		if (personaje == 0) {
			isPunching_left = player->isPunching_left();
			isPunching_right = player->isPunching_right();
			isKicking_left = player->isKicking_left();
			isKicking_right = player->isKicking_right();
		}
		else if (personaje == 1) {
			isPunching_left = kim->isPunching_left();
			isPunching_right = kim->isPunching_right();
			isKicking_left = kim->isKicking_left();
			isKicking_right = kim->isKicking_right();
		}
		else if (personaje == 2) {
			isPunching_left = ramona->isPunching_left();
			isPunching_right = ramona->isPunching_right();
			isKicking_left = ramona->isKicking_left();
			isKicking_right = ramona->isKicking_right();
		}
		if (enemigo == 1) posEnemy = enemigo1[i]->getPosition();
		if (enemigo == 2) posEnemy = enemigo2[i]->getPosition();
		if (enemigo == 3) posEnemy = enemigo3[i]->getPosition();
		
		if ((posPlayer.x > posEnemy.x - 35) && (posPlayer.x < posEnemy.x + 20) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 70)) {
			if (rand() % 120 == 3) {
				if (!isPunching_right && !isKicking_right && !isDead && !isRecuperando) {
					if (enemigo == 1) enemigo1[i]->atacarPuñetadosIzquierda();
					if (enemigo == 2) enemigo2[i]->atacarPuñetadosIzquierda();
					if (enemigo == 3) enemigo3[i]->atacarPuñetadosIzquierda();
					if (personaje == 0) player->recibirPuñetazoDerecha(vida_quitada);
					else if (personaje == 1) kim->recibirPuñetazoDerecha(vida_quitada);
					else if (personaje == 2) ramona->recibirPuñetazoDerecha(vida_quitada);
					if (enemigo == 1) atacando1[i] = true;
					if (enemigo == 2) atacando2[i] = true;
					if (enemigo == 3) atacando3[i] = true;
				}
			}
		}

		else if ((posEnemy.x + 80 >= posPlayer.x - 5 && posEnemy.x + 10 < posPlayer.x) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 70)) {
			if (rand() % 100 == 3) {
				if (!isPunching_left && !isKicking_left && !isDead && !isRecuperando) {
					if (enemigo == 1) enemigo1[i]->atacarPuñetazosDerecha();
					if (enemigo == 2) enemigo2[i]->atacarPuñetazosDerecha();
					if (enemigo == 3) enemigo3[i]->atacarPuñetazosDerecha();
					if (personaje == 0) player->recibirPuñetazoIzquierda(vida_quitada);
					else if (personaje == 1) kim->recibirPuñetazoIzquierda(vida_quitada);
					else if (personaje == 2) ramona->recibirPuñetazoIzquierda(vida_quitada);
					if (enemigo == 1) atacando1[i] = true;
					if (enemigo == 2) atacando2[i] = true;
					if (enemigo == 3) atacando3[i] = true;
				}
			}
		}

		else {
			if (enemigo == 1) atacando1[i] = false;
			if (enemigo == 2) atacando2[i] = false;
			if (enemigo == 3) atacando3[i] = false;
		}

		if (rand() % 200 == 2) {
			if (enemigo == 1) atacando1[i] = false;
			if (enemigo == 2) atacando2[i] = false;
			if (enemigo == 3) atacando3[i] = false;
		}
	
		bool atack;
		if (enemigo == 1) atack = atacando1[i];
		if (enemigo == 2) atack = atacando2[i];
		if (enemigo == 3) atack = atacando3[i];

		if ((enemigo1[i]->isPunchingLeft() || enemigo1[i]->isPunchingRight()) && !enemigo1[i]->isDeath() && !atack && enemigo == 1) {
			if (enemigo == 1) enemigo1[i]->turnToWalk();
			if (personaje == 0 && !player->isRecuperando()) player->turnToWalk();
			else if (personaje == 1 && !kim->isRecuperando()) kim->turnToWalk();
			else if (personaje == 2 && !ramona->isRecuperando()) ramona->turnToWalk();
		}
		else if ((enemigo2[i]->isPunchingLeft() || enemigo2[i]->isPunchingRight()) && !enemigo2[i]->isDeath() && !atack && enemigo == 2) {
			if (enemigo == 2) enemigo2[i]->turnToWalk();
			if (personaje == 0 && !player->isRecuperando()) player->turnToWalk();
			else if (personaje == 1 && !kim->isRecuperando()) kim->turnToWalk();
			else if (personaje == 2 && !ramona->isRecuperando()) ramona->turnToWalk();
		}
		else if ((enemigo3[i]->isPunchingLeft() || enemigo3[i]->isPunchingRight()) && !enemigo3[i]->isDeath() && !atack && enemigo == 3) {
			if (enemigo == 3) enemigo3[i]->turnToWalk();
			if (personaje == 0 && !player->isRecuperando()) player->turnToWalk();
			else if (personaje == 1 && !kim->isRecuperando()) kim->turnToWalk();
			else if (personaje == 2 && !ramona->isRecuperando()) ramona->turnToWalk();
		}	
	}
}

void Level1::comprobarLuchaBoss(glm::vec2 posPlayer) {
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right, isPunching_up_left, isPunching_up_right;
	if (personaje == 0) {
		isPunching_left = player->isPunching_left();
		isPunching_right = player->isPunching_right();
		isKicking_left = player->isKicking_left();
		isKicking_right = player->isKicking_right();
		isPunching_up_left = player->isPunching_up_left();
		isPunching_up_right = player->isPunching_up_right();
	}
	else if (personaje == 1) {
		isPunching_left = kim->isPunching_left();
		isPunching_right = kim->isPunching_right();
		isKicking_left = kim->isKicking_left();
		isKicking_right = kim->isKicking_right();
		isPunching_up_left = kim->isPunching_up_left();
		isPunching_up_right = kim->isPunching_up_right();
	}
	else if (personaje == 2) {
		isPunching_left = ramona->isPunching_left();
		isPunching_right = ramona->isPunching_right();
		isKicking_left = ramona->isKicking_left();
		isKicking_right = ramona->isKicking_right();
		isPunching_up_left = ramona->isPunching_up_left();
		isPunching_up_right = ramona->isPunching_up_right();
	}
	posEnemy = boss->getPosition();
	if ((posPlayer.x <= (posEnemy.x + 90) && (posPlayer.x - 30 > posEnemy.x)) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 60)) {
		if (isPunching_left) {
			boss->recibirPuñetazoDerecha();
		}
		else if (isKicking_left) {
			boss->recibirPatadaDerecha();
		}
		else if (isPunching_up_left) {
			boss->recibirPuñetazoArribaDerecha();
		}
		else boss->setGolpesto0();
	}

	else if ((posPlayer.x >= posEnemy.x - 30 && posPlayer.x < posEnemy.x + 20) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 60)) {
		if (isPunching_right) {
			boss->recibirPuñetazoIzquierda();
		}
		else if (isKicking_right) {
			boss->recibirPatadaIzquierda();
		}
		else if (isPunching_up_right) {
			boss->recibirPuñetazoArribaIzquierda();
		}
		else boss->setGolpesto0();
	}
}

void Level1::comprobarAtaqueBoss(glm::vec2 posPlayer) {
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right;
	if (!boss->isDeath() && !boss->isDying() && !boss->isRecuperando()) {
		if (personaje == 0) {
			isPunching_left = player->isPunching_left();
			isPunching_right = player->isPunching_right();
			isKicking_left = player->isKicking_left();
			isKicking_right = player->isKicking_right();
		}
		else if (personaje == 1) {
			isPunching_left = kim->isPunching_left();
			isPunching_right = kim->isPunching_right();
			isKicking_left = kim->isKicking_left();
			isKicking_right = kim->isKicking_right();
		}
		else if (personaje == 2) {
			isPunching_left = ramona->isPunching_left();
			isPunching_right = ramona->isPunching_right();
			isKicking_left = ramona->isKicking_left();
			isKicking_right = ramona->isKicking_right();
		}
		posEnemy = boss->getPosition();

		if ((posPlayer.x > posEnemy.x - 35) && (posPlayer.x < posEnemy.x + 20) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 50)) {
			if (rand() % 120 == 3) {
				if (!isPunching_right && !isKicking_right && !boss->isDeath() && !boss->isRecuperando()) {
					boss->atacarPuñetadosIzquierda();
					if (personaje == 0) player->recibirPuñetazoDerecha(20);
					else if (personaje == 1) kim->recibirPuñetazoDerecha(20);
					else if (personaje == 2) ramona->recibirPuñetazoDerecha(20);
					atacando_boss = true;
				}
			}
		}

		else if ((posEnemy.x + 80 >= posPlayer.x - 5 && posEnemy.x + 10 < posPlayer.x) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 50)) {
			if (rand() % 100 == 3) {
				if (!isPunching_left && !isKicking_left && !boss->isDeath() && !boss->isRecuperando()) {
					boss->atacarPuñetazosDerecha();
					if (personaje == 0) player->recibirPuñetazoIzquierda(20);
					else if (personaje == 1) kim->recibirPuñetazoIzquierda(20);
					else if (personaje == 2) ramona->recibirPuñetazoIzquierda(20);
					atacando_boss = true;
				}
			}
		}

		else atacando_boss = false;
		if (rand() % 200 == 2) atacando_boss = false;


		if ((boss->isPunchingLeft() || boss->isPunchingRight()) && !boss->isDeath() && !atacando_boss) {
			boss->turnToWalk();
			if (personaje == 0 && !player->isRecuperando()) player->turnToWalk();
			else if (personaje == 1 && !kim->isRecuperando()) kim->turnToWalk();
			else if (personaje == 2 && !ramona->isRecuperando()) ramona->turnToWalk();
		}
	}
}

void Level1::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");

	simpleTexProgram.init();
	simpleTexProgram.addShader(vShader);
	simpleTexProgram.addShader(fShader);
	simpleTexProgram.link();
	if (!simpleTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleTexProgram.log() << endl << endl;
	}
	simpleTexProgram.bindFragmentOutput("outColor");
}





