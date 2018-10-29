#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level2.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 50
#define INIT_PLAYER_Y_TILES 150


Level2::Level2()
{
	
}

Level2::~Level2()
{
}


void Level2::init(bool music, int pers)
{
	if (music) {
		mciSendString(TEXT("stop sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/Level2.mp3 repeat"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/Level2.mp3 volume to 98"), NULL, 0, NULL);
	}
	else {
		//	mciSendString(TEXT("stop sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("stop sounds/SOUND/20.mp3"), NULL, 0, NULL);
	}
	musica = music;
	currentTime = 0.0f;
	initShaders();
	personaje = pers;


	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(620, 340.f) };
	texCoords[0] = glm::vec2(0, 0); texCoords[1] = glm::vec2(1, 1);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, simpleTexProgram);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, simpleTexProgram);
	texs[0].loadFromFile("images/Levels/level2new.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	texs[1].loadFromFile("images/sombra.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].setMagFilter(GL_NEAREST);

	hud.init(personaje, texProgram, simpleTexProgram);

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
	for (int i = 0; i < 6; ++i) {
		enemigo1[i] = new Enemigo1();
		enemigo1[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
		enemigo1[i]->setPosition(glm::vec2(100, 260));
	}
	
	boss = new Boss1();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), simpleTexProgram);
	boss->setPosition(glm::vec2(3120, 240));

	x = 0.f;
	projection = glm::ortho(0.f, 100.0f, float(SCREEN_HEIGHT - 1), 0.f);

}

void Level2::update(int deltaTime)
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

	if (x < 458) {
		if (pos.x >= 380 && isWalking) {
			x += 0.4f;
			projection = glm::ortho(min(max(0, 0 + x), 0 + 460), min(max(100, 100 + x), 100 + 460), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 6; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose = enemigo1[i]->getPosition();
					if (x < 460) pose.x -= 2.57f;
					enemigo1[i]->setPosition(pose);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x < 460) pose.x -= 2.57f;
			boss->setPosition(pose);
		}
		else if (pos.x <= 200 && isWalking) {
			x -= 0.4f;
			projection = glm::ortho(min(max(0, 0 + x), 460), min(max(100, 100 + x), 100 + 460), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 6; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose = enemigo1[i]->getPosition();
					if (x > 0) pose.x += 2.57f;
					enemigo1[i]->setPosition(pose);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x < 0) pose.x += 2.57f;
			boss->setPosition(pose);
		}
		else if (pos.x >= 380 && isRunning) {
			x += 0.705f;
			projection = glm::ortho(min(max(0, 0 + x), 459), min(max(100, 100 + x), 100 + 460), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 6; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose = enemigo1[i]->getPosition();
					if (x < 460) pose.x -= 2.6f*1.725f;
					enemigo1[i]->setPosition(pose);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x < 460) pose.x -= 2.6f*1.725f;
			boss->setPosition(pose);
		}
		else if (pos.x <= 200 && isRunning) {
			x -= 0.705f;
			projection = glm::ortho(min(max(0, 0 + x), 0 + 460), min(max(100, 100 + x), 100 + 460), float(SCREEN_HEIGHT - 1), 0.f);
			for (int i = 0; i < 6; ++i) {
				if (!enemigo1[i]->isCompletlyDeath()) {
					glm::vec2 pose = enemigo1[i]->getPosition();
					if (x > 0) pose.x += 2.6f*1.725f;
					enemigo1[i]->setPosition(pose);
				}
			}
			glm::vec2 pose = boss->getPosition();
			if (x < 0) pose.x += 2.6f*1.725f;
			boss->setPosition(pose);
		}
		if (x <= 0) x = 0.f;
		else if (x > 460) x = 218.f;
		for (int i = 0; i < 6; ++i) {
			comprobarLucha(i, pos);
			comprobarAtaqueEnemigo(i, pos);
			enemigo1[i]->update(deltaTime);
		}
	}

	else if (x != 460) {
		x = 460;
		projection = glm::ortho(float(x), float(x + 100), float(SCREEN_HEIGHT - 1), 0.f);
		mciSendString(TEXT("stop sounds/SOUND/level2.mp3"), NULL, 0, NULL);
		if (musica) {
			mciSendString(TEXT("play sounds/SOUND/boss.mp3 repeat"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio sounds/SOUND/boss.mp3 volume to 98"), NULL, 0, NULL);
		}
	}
	yplayer = pos.y;

	comprobarLuchaBoss(pos);
	comprobarAtaqueBoss(pos);
	boss->update(deltaTime);
	if (personaje == 0) hud.changeLife(player->getVida());
	else if (personaje == 1) hud.changeLife(kim->getVida());
	else hud.changeLife(ramona->getVida());
	hud.update(deltaTime);
}

void Level2::render()
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
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
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
			modelview2 = glm::translate(modelview2, glm::vec3(pos.x, y + 80, 0.f));
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

	//renderizamos sombras enemigas
	int i;
	for (i = 0; i < 6; ++i) {
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
	}
	//sombra boss
	if (!boss->isDying() && !boss->isCompletlyDeath()) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(boss->getPosition().x + 20, boss->getPosition().y + 125, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.06f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}
	else if (boss->isDying() && !boss->isCompletlyDeath()) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(boss->getPosition().x + 20, boss->getPosition().y + 140, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.06f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);

	for (i = 0; i < 6; ++i) {
		if (enemigo1[i]->getPosition().y + 40 <= yplayer && !enemigo1[i]->isCompletlyDeath() && !enemigo1[i]->isDeath() && !enemigo1[i]->isDying()) {
			enemigo1[i]->render();
		}
		else if (enemigo1[i]->getPosition().y <= yplayer - 10 && !enemigo1[i]->isCompletlyDeath() && (enemigo1[i]->isDeath() || enemigo1[i]->isDying())) {
			enemigo1[i]->render();
		}
		else enemigo1[i]->free();
	}

	if (personaje == 0) player->render();
	else if (personaje == 1) kim->render();
	else if (personaje == 2) ramona->render();

	for (i = 0; i < 6; ++i) {
		if (enemigo1[i]->getPosition().y + 40 > yplayer && !enemigo1[i]->isCompletlyDeath() && !enemigo1[i]->isDeath() && !enemigo1[i]->isDying()) enemigo1[i]->render();
		else if (enemigo1[i]->getPosition().y > yplayer - 10 && !enemigo1[i]->isCompletlyDeath() && (enemigo1[i]->isDeath() || enemigo1[i]->isDying())) enemigo1[i]->render();
		else enemigo1[i]->free();
	}

	
	boss->render();
	hud.render();



}

void Level2::initShaders()
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


void Level2::comprobarLucha(int i, glm::vec2 posPlayer) {
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
	posEnemy = enemigo1[i]->getPosition();
	if ((posPlayer.x <= (posEnemy.x + 90) && (posPlayer.x - 30 > posEnemy.x)) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 60)) {
		if (isPunching_left) {
			enemigo1[i]->recibirPuñetazoDerecha();
		}
		else if (isKicking_left) {
			enemigo1[i]->recibirPatadaDerecha();
		}
		else if (isPunching_up_left) {
			enemigo1[i]->recibirPuñetazoArribaDerecha();
		}
		else enemigo1[i]->setGolpesto0();
	}

	else if ((posPlayer.x >= posEnemy.x - 30 && posPlayer.x < posEnemy.x + 20) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 60)) {
		if (isPunching_right) {
			enemigo1[i]->recibirPuñetazoIzquierda();
		}
		else if (isKicking_right) {
			enemigo1[i]->recibirPatadaIzquierda();
		}
		else if (isPunching_up_right) {
			enemigo1[i]->recibirPuñetazoArribaIzquierda();
		}
		else enemigo1[i]->setGolpesto0();
	}
}

void Level2::comprobarAtaqueEnemigo(int i, glm::vec2 posPlayer) {
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right;
	if (!enemigo1[i]->isDeath() && !enemigo1[i]->isDying()) {
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
		posEnemy = enemigo1[i]->getPosition();

		if ((posPlayer.x > posEnemy.x - 35) && (posPlayer.x < posEnemy.x + 20) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 50)) {
			if (rand() % 120 == 3) {
				if (!isPunching_right && !isKicking_right && !enemigo1[i]->isDeath() && !enemigo1[i]->isRecuperando()) {
					enemigo1[i]->atacarPuñetadosIzquierda();
					if (personaje == 0) player->recibirPuñetazoDerecha();
					else if (personaje == 1) kim->recibirPuñetazoDerecha();
					else if (personaje == 2) ramona->recibirPuñetazoDerecha();
					atacando[i] = true;
				}
			}
		}

		else if ((posEnemy.x + 80 >= posPlayer.x - 5 && posEnemy.x + 10 < posPlayer.x) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 50)) {
			if (rand() % 100 == 3) {
				if (!isPunching_left && !isKicking_left && !enemigo1[i]->isDeath() && !enemigo1[i]->isRecuperando()) {
					enemigo1[i]->atacarPuñetazosDerecha();
					if (personaje == 0) player->recibirPuñetazoIzquierda();
					else if (personaje == 1) kim->recibirPuñetazoIzquierda();
					else if (personaje == 2) ramona->recibirPuñetazoIzquierda();
					atacando[i] = true;
				}
			}
		}

		else atacando[i] = false;
		if (rand() % 200 == 2) atacando[i] = false;


		if ((enemigo1[i]->isPunchingLeft() || enemigo1[i]->isPunchingRight()) && !enemigo1[i]->isDeath() && !atacando[i]) {
			enemigo1[i]->turnToWalk();
			if (personaje == 0 && !player->isRecuperando()) player->turnToWalk();
			else if (personaje == 1 && !kim->isRecuperando()) kim->turnToWalk();
			else if (personaje == 2 && !ramona->isRecuperando()) ramona->turnToWalk();
		}
	}
}

void Level2::comprobarLuchaBoss(glm::vec2 posPlayer) {
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

void Level2::comprobarAtaqueBoss(glm::vec2 posPlayer) {
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right;
	if (!boss->isDeath() && !boss->isDying()) {
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
					if (personaje == 0) player->recibirPuñetazoDerecha();
					else if (personaje == 1) kim->recibirPuñetazoDerecha();
					else if (personaje == 2) ramona->recibirPuñetazoDerecha();
					atacando_boss = true;
				}
			}
		}

		else if ((posEnemy.x + 80 >= posPlayer.x - 5 && posEnemy.x + 10 < posPlayer.x) && (posPlayer.y >= posEnemy.y + 40 && posPlayer.y <= posEnemy.y + 50)) {
			if (rand() % 100 == 3) {
				if (!isPunching_left && !isKicking_left && !boss->isDeath() && !boss->isRecuperando()) {
					boss->atacarPuñetazosDerecha();
					if (personaje == 0) player->recibirPuñetazoIzquierda();
					else if (personaje == 1) kim->recibirPuñetazoIzquierda();
					else if (personaje == 2) ramona->recibirPuñetazoIzquierda();
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