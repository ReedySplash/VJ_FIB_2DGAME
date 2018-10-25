#include "Hud.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>



Hud::Hud()
{
}


Hud::~Hud()
{
}

void Hud::init(int person, ShaderProgram &shader, ShaderProgram& simple) {
	personaje = person; 
	texProgram = shader;
	simpleProgram = simple;
	quad = Quad::createQuad(0.f, 0.f, 500.f, 500.f, simpleProgram);
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(640), float(480)) };
	glm::vec2 texCoords[2];
	texCoords[0] = glm::vec2(0, 0); texCoords[1] = glm::vec2(1, 1);

	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, shader);
	texs[0].loadFromFile("images/Hud/health-bar-png-5.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
}

void Hud::update(int deltaTime) {
	currentTime += deltaTime;
}

void Hud::render() {
	glm::mat4 modelview;

	simpleProgram.use();

	simpleProgram.use();
	simpleProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(640), float(480 - 1), 0.f));
	simpleProgram.setUniform4f("color", 0.2f, 0.2f, 0.8f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(128.f, 48.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	simpleProgram.setUniformMatrix4f("modelview", modelview);
	quad->render();

	texProgram.use();
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(640), float(480 - 1), 0.f));
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	modelview = glm::translate(modelview, glm::vec3(20.f, -5.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 0.3f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);
}

void Hud::changeLife(int life) {

}