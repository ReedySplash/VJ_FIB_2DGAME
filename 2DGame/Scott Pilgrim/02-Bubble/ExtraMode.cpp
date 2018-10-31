#include "ExtraMode.h"



ExtraMode::ExtraMode()
{
}


ExtraMode::~ExtraMode()
{
}

void ExtraMode::init(bool music) {

	if (music) {
		mciSendString(TEXT("stop sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/ExtraTheme.mp3 repeat"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/ExtraTheme.mp3 volume to 98"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("stop sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
	}
	musica = music;
	currentTime = 0.0f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(1.f, 1.f) };

	initShaders();
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/battleRoyale/Mapa.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	texs[1].loadFromFile("images/sombra.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].setMagFilter(GL_NEAREST);
	projection = glm::ortho(60.f, 580.f, float(SCREEN_HEIGHT - 1), 0.f);

	//Init player
	player = new Player();
	player->init(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), texProgram, 3);
	player->setPosition(glm::vec2(164, 198));
	ramona = new Ramona();
	ramona->init(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), texProgram, 3);
	ramona->setPosition(glm::vec2(416, 198));
	hud.init(1,texProgram,simpleTexProgram);
	hud2.init(2, texProgram, simpleTexProgram);
	
}

bool ExtraMode::update(int deltaTime) {
	currentTime += deltaTime;
	player->update(deltaTime);
	ramona->update(deltaTime);
	comprobarLucha();
	hud.changeLife(player->getVida());
	hud2.changeLife(ramona->getVida());
	hud.update(deltaTime);
	hud2.update(deltaTime);
	return true;
}

void ExtraMode::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);

	texProgram.use();
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT - 1), 0.f));
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	glm::mat4 modelview2;
	jumping = player->isJumping();
	if (!jumping && !player->isRecuperando() && player->getVida() > 0) y = player->getPosition().y;
	if (jumping) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(player->getPosition().x, y + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}
	else if (player->isRecuperando()) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(player->getPosition().x, y + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	else if (player->getVida() <= 0) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(player->getPosition().x, y + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	else {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(player->getPosition().x, player->getPosition().y + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	jumping2 = ramona->isJumping();
	if (!jumping2 && !ramona->isRecuperando() && ramona->getVida() > 0) y_ramona = ramona->getPosition().y;
	if (jumping2) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(ramona->getPosition().x, y_ramona + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}
	else if (ramona->isRecuperando()) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(ramona->getPosition().x, y_ramona + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	else if (ramona->getVida() <= 0) {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(ramona->getPosition().x, y_ramona + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	else {
		modelview2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview2 = glm::translate(modelview2, glm::vec3(ramona->getPosition().x, ramona->getPosition().y + 80, 0.f));
		modelview2 = glm::scale(modelview2, glm::vec3(0.08f, 0.07f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview2);
		texQuad[1]->render(texs[1]);
	}

	if (y_ramona > y) {
		player->render();
		ramona->render();
	}
	else {
		ramona->render();
		player->render();
	}

	hud.render();
	hud2.render();
}


void ExtraMode::comprobarLucha() {
	glm::fvec2 posPlayer = player->getPosition();
	glm::fvec2 posEnemy = ramona->getPosition();
	bool isPunching_left, isKicking_left, isPunching_right, isKicking_right, isPunching_up_left, isPunching_up_right;
	bool isPunching_left_ra, isKicking_left_ra, isPunching_right_ra, isKicking_right_ra, isPunching_up_left_ra, isPunching_up_right_ra;
	isPunching_left = player->isPunching_left();
	isPunching_right = player->isPunching_right();
	isKicking_left = player->isKicking_left();
	isKicking_right = player->isKicking_right();
	isPunching_up_left = player->isPunching_up_left();
	isPunching_up_right = player->isPunching_up_right();

	isPunching_left_ra = ramona->isPunching_left();
	isPunching_right_ra = ramona->isPunching_right();
	isKicking_left_ra = ramona->isKicking_left();
	isKicking_right_ra = ramona->isKicking_right();
	isPunching_up_left_ra = ramona->isPunching_up_left();
	isPunching_up_right_ra = ramona->isPunching_up_right();

	if ((posPlayer.x <= (posEnemy.x + 10) && (posPlayer.x >= posEnemy.x - 40)) && (posPlayer.y <= posEnemy.y + 10 && posPlayer.y >= posEnemy.y - 10)) {
		if (isPunching_right|| isKicking_right || isPunching_up_right || isPunching_up_right) {
			ramona->recibirPuñetazoIzquierda();
			atacando = true;
		}
		else if (isPunching_left_ra || isKicking_left_ra || isPunching_up_left_ra || isPunching_up_left_ra) {
			player->recibirPuñetazoDerecha();
			atacando_ra = true;
		}
	}

	else if ((posPlayer.x >= posEnemy.x - 10 && posPlayer.x < posEnemy.x + 40) && (posPlayer.y <= posEnemy.y + 10 && posPlayer.y >= posEnemy.y - 10)) {
		if (isPunching_left || isKicking_left || isPunching_up_left || isPunching_up_left) {
			ramona->recibirPuñetazoDerecha();
			atacando = true;
		}
		else if (isPunching_right_ra || isKicking_right_ra || isPunching_up_right_ra || isPunching_up_right_ra) {
			player->recibirPuñetazoIzquierda();
			atacando_ra = true;
		}
	}
	else {
		if (atacando && !isPunching_left && !isPunching_right && !isKicking_left && !isKicking_right && !isPunching_up_left && !isPunching_up_right) {
			player->turnToWalk();
			atacando = false;
		}
		if (atacando_ra && !isPunching_left_ra && !isPunching_right_ra && !isKicking_left_ra && !isKicking_right_ra && !isPunching_up_left_ra && !isPunching_up_right_ra) {
			ramona->turnToWalk();
			atacando_ra = false;
		}
	}
}


void ExtraMode::initShaders()
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