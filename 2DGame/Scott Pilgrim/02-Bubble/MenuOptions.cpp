#include "MenuOptions.h"
#include "Game.h"


MenuOptions::MenuOptions()
{
}


MenuOptions::~MenuOptions()
{
}

void MenuOptions::init(bool music)
{
	if (music) {
		mciSendString(TEXT("stop sounds/SOUND/Level1.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/MenuTheme.mp3 repeat"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/MenuTheme.mp3 to volume 95"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("stop sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
	}
	musica = music;
	currentTime = 0.0f;
	play = false;
	credits = false;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(640), float(480)) };
	glm::vec2 texCoords[2];

	initShaders();
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/MenuOptions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	projection = glm::ortho(0.f, float(640 - 1), float(480 - 1), 0.f);
	opcion = 0;
	musica_string[0] = {"Music On"};
	musica_string[1] = { "Music Off"};


	if (!black.init("fonts/pixeldu.ttf"))
		cout << "Could not load font!!!" << endl;
}

void MenuOptions::update(int deltaTime)
{
	currentTime += deltaTime;
	if (play) slevel.update(deltaTime);
	else if (credits) {

	}
	else {
		if (musica) text_music = musica_string[0];
		else text_music = musica_string[1];
	}
}

void MenuOptions::render()
{
	if (!play && !credits) {
		glm::mat4 modelview;

		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview);
		texQuad[0]->render(texs[0]);

		if (glutGet(GLUT_WINDOW_WIDTH) == 1280) {
			if (opcion == 0) black.render("Play", glm::vec2(720, 420), 56, glm::vec4(0, 0, 0, 1));
			else black.render("Play", glm::vec2(740, 420), 56, glm::vec4(1, 1, 1, 1));
		}
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920) {
			if (opcion == 0) black.render("Play", glm::vec2(1040, 620), 65, glm::vec4(0, 0, 0, 1));
			else black.render("Play", glm::vec2(1080, 620), 65, glm::vec4(1, 1, 1, 1));
		}

		if (glutGet(GLUT_WINDOW_WIDTH) == 1280) {
			if (opcion == 1) black.render(text_music, glm::vec2(720, 520), 56, glm::vec4(0, 0, 0, 1));
			else black.render(text_music, glm::vec2(740, 520), 56, glm::vec4(1, 1, 1, 1));;
		}
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920) {
			if (opcion == 1) black.render(text_music, glm::vec2(1040, 770), 65, glm::vec4(0, 0, 0, 1));
			else black.render(text_music, glm::vec2(1080, 770), 65, glm::vec4(1, 1, 1, 1));;
		}

		if (glutGet(GLUT_WINDOW_WIDTH) == 1280) {
			if (opcion == 2) black.render("Credits", glm::vec2(720, 620), 56, glm::vec4(0, 0, 0, 1));
			else black.render("Credits", glm::vec2(740, 620), 56, glm::vec4(1, 1, 1, 1));
		}
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920) {
			if (opcion == 2) black.render("Credits", glm::vec2(1040, 920), 65, glm::vec4(0, 0, 0, 1));
			else black.render("Credits", glm::vec2(1080, 920), 65, glm::vec4(1, 1, 1, 1));
		}
	}
	else if (!play && credits) {

	}
	else {
		slevel.render();
	}
}


void MenuOptions::upOption() {
	if (!play) {
		++opcion;
		if (opcion == 3) opcion = 0;
	}
}

void MenuOptions::downOption() {
	if (!play) {
		--opcion;
		if (opcion == -1) opcion = 2;
	}
}

void MenuOptions::changeCharLeft() {
	if (play) slevel.left();
}

void MenuOptions::changeCharRight() {
	if (play) slevel.right();
}

void MenuOptions::changeMusica() {
	if (!musica && opcion == 1) {
		musica = true;
		mciSendString(TEXT("play sounds/SOUND/MenuTheme.mp3 repeat"), NULL, 0, NULL);
		mciSendString(TEXT("setaudio sounds/SOUND/MenuTheme.mp3 to volume 95"), NULL, 0, NULL);
	}
	else if (opcion == 1) {
		musica = false;
		mciSendString(TEXT("pause sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
	}
}

void MenuOptions::playGame() {
	if (opcion == 0 && !play) {
		play = true;
		slevel.init(simpleTexProgram, texProgram);
	}
}

void MenuOptions::showCredits() {
	if (opcion == 2) credits = true;
	else credits = false;
}

int MenuOptions::getLevel() {
	return slevel.getLevel();
}

bool MenuOptions::getMusic() {
	return musica;
}

int MenuOptions::getPersonaje() {
	return slevel.getPersonaje();
}

void MenuOptions::initShaders()
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
	simpleTexProgram.init();
	simpleTexProgram.addShader(vShader);
	simpleTexProgram.addShader(fShader);
	simpleTexProgram.link();
	simpleTexProgram.link();
	if (!simpleTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleTexProgram.log() << endl << endl;
	}
	simpleTexProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
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
}