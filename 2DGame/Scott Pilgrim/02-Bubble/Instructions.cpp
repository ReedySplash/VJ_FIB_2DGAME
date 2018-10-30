#include "Instructions.h"
#include "Game.h"


Instructions::Instructions()
{
}


Instructions::~Instructions()
{
}

void Instructions::init(ShaderProgram &prog) {

	texProgram = prog;
	currentTime = 0.0f;
	inst = 0;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(1.f, 1.f) };
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/instrucciones.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

bool Instructions::update(int deltaTime) {
	currentTime += deltaTime;
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) || Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		if (inst == 1) inst = 0;
		else inst = 1;
		Sleep(150);
	}
	if (inst == 0) {
		texs[0].loadFromFile("images/instrucciones.png", TEXTURE_PIXEL_FORMAT_RGBA);
		texs[0].setMagFilter(GL_NEAREST);
	}
	else {
		texs[0].loadFromFile("images/instrucciones2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		texs[0].setMagFilter(GL_NEAREST);
	}
	return true;

}

void Instructions::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);
}
