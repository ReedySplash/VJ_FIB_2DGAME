#include "SLevelAPlayer.h"
#include "Game.h"


SLevelAPlayer::SLevelAPlayer()
{
}


SLevelAPlayer::~SLevelAPlayer()
{
}

void SLevelAPlayer::init(ShaderProgram &simpleTexProgram, ShaderProgram &texProgram)
{
	
	currentTime = 0.0f;
	this->simpleTexProgram = simpleTexProgram;
	this->texProgram = texProgram;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(640), float(480)) };
	glm::vec2 texCoords[2];
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/SelectLevelAndChar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	projection = glm::ortho(0.f, float(640 - 1), float(480 - 1), 0.f);

	initShaders();

	if (!text.init("fonts/pixeldu.ttf"))
		cout << "Could not load font!!!" << endl;

	spritesheet_Scott.loadFromFile("images/Scott/Scott quieto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_Scott = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.125, 1), &spritesheet_Scott, &texProgram);
	sprite_Scott->setNumberAnimations(1);

	sprite_Scott->setAnimationSpeed(0, 8);
	sprite_Scott->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_Scott->addKeyframe(0, glm::vec2(0.125, 0.f));
	sprite_Scott->addKeyframe(0, glm::vec2(0.25, 0.f));
	sprite_Scott->addKeyframe(0, glm::vec2(0.375, 0.f));
	sprite_Scott->addKeyframe(0, glm::vec2(0.5, 0.f));
	sprite_Scott->addKeyframe(0, glm::vec2(0.625f, 0.f));
	sprite_Scott->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite_Scott->addKeyframe(0, glm::vec2(0.875f, 0.f));

	spritesheet_Kim.loadFromFile("images/Kim/Kim_stand_right.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_Kim = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.25, 1), &spritesheet_Kim, &texProgram);
	sprite_Kim->setNumberAnimations(1);

	sprite_Kim->setAnimationSpeed(0, 8);
	sprite_Kim->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_Kim->addKeyframe(0, glm::vec2(0.25f, 0.f));
	sprite_Kim->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite_Kim->addKeyframe(0, glm::vec2(0.75f, 0.f));

	spritesheet_Ramona.loadFromFile("images/Ramona/RamonaQuieta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_Ramona = Sprite::createSprite(glm::ivec2(45, 100), glm::vec2(0.16666667, 1), &spritesheet_Ramona, &texProgram);
	sprite_Ramona->setNumberAnimations(1);

	sprite_Ramona->setAnimationSpeed(0, 8);
	sprite_Ramona->addKeyframe(0, glm::vec2(0.0f, 0.f));
	sprite_Ramona->addKeyframe(0, glm::vec2(0.16666667, 0.f));
	sprite_Ramona->addKeyframe(0, glm::vec2(0.16666667 * 2, 0.f));
	sprite_Ramona->addKeyframe(0, glm::vec2(0.16666667 * 3, 0.f));
	sprite_Ramona->addKeyframe(0, glm::vec2(0.16666667 * 4, 0.f));
	sprite_Ramona->addKeyframe(0, glm::vec2(0.16666667 * 5, 0.f));

	sprite_Scott->changeAnimation(0);
	sprite_Kim->changeAnimation(0);
	sprite_Ramona->changeAnimation(0);

	sprite_Scott->setPosition(glm::vec2(float(300), float(170)));
	sprite_Kim->setPosition(glm::vec2(float(300), float(170)));
	sprite_Ramona->setPosition(glm::vec2(float(300), float(170)));

	comenzar = false;
	level_num = 0;
}

void SLevelAPlayer::update(int deltaTime)
{
	currentTime += deltaTime;
	sprite_Kim->update(deltaTime);
	sprite_Ramona->update(deltaTime);
	sprite_Scott->update(deltaTime);

	if (Game::instance().getSpecialKey(103)) {
		if (level_num == 0) level_num = 1;
		else if (level_num == 1) level_num = 0;
		Sleep(150);
	}

	else if (Game::instance().getSpecialKey(101)) {
		if(level_num == 0) level_num = 1;
		else if(level_num == 1) level_num = 0;
		Sleep(150);
	}

	else if (Game::instance().getKey(13)) {
		comenzar = true;
	}

}

void SLevelAPlayer::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);

	if (personaje == 0) {
		sprite_Scott->render();
		if (glutGet(GLUT_WINDOW_WIDTH) == 1280)
			text.render("Scott", glm::vec2(565, 450), 36, glm::vec4(1, 1, 1, 1));
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920)
			text.render("Scott", glm::vec2(868, 640), 48, glm::vec4(1, 1, 1, 1));
	}

	else if (personaje == 1) {
		sprite_Kim->render();
		if (glutGet(GLUT_WINDOW_WIDTH) == 1280)
			text.render("Kim", glm::vec2(613, 450), 36, glm::vec4(1, 1, 1, 1));
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920)
			text.render("Kim", glm::vec2(924, 640), 48, glm::vec4(1, 1, 1, 1));
	}

	else {
		sprite_Ramona->render();
		if (glutGet(GLUT_WINDOW_WIDTH) == 1280)
			text.render("Ramona", glm::vec2(548, 450), 36, glm::vec4(1, 1, 1, 1));
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920)
			text.render("Ramona", glm::vec2(845, 640), 48, glm::vec4(1, 1, 1, 1));
	}

	if (level_num == 0) {
		if (glutGet(GLUT_WINDOW_WIDTH) == 1280)
			text.render("Level 1", glm::vec2(470, 600), 60, glm::vec4(1, 1, 1, 1));
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920)
			text.render("Level 1", glm::vec2(722, 900), 90, glm::vec4(1, 1, 1, 1));
	}

	else {
		if (glutGet(GLUT_WINDOW_WIDTH) == 1280)
			text.render("Level 2", glm::vec2(470, 600), 60, glm::vec4(1, 1, 1, 1));
		else if (glutGet(GLUT_WINDOW_WIDTH) == 1920)
			text.render("Level 2", glm::vec2(722, 900), 90, glm::vec4(1, 1, 1, 1));
	}
}

void SLevelAPlayer::right() {
	++personaje;
	if (personaje == 3) personaje = 0;
}

void SLevelAPlayer::left() {
	--personaje;
	if (personaje == -1) personaje = 2;
}

int SLevelAPlayer::getLevel() {
	if (comenzar) {
		int num = level_num;
		level_num = -1;
		comenzar = false;
		return num;
	}
	return -1;
}

int SLevelAPlayer::getPersonaje() {
	return personaje;
}

void SLevelAPlayer::initShaders()
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