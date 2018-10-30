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
	currentVida = 100;
	vidaInicial = 100;
	quad = Quad::createQuad(0.f, 0.f, 500.f, 500.f, simpleProgram);
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(640), float(480)) };
	glm::vec2 texCoords[2];
	texCoords[0] = glm::vec2(0, 0); texCoords[1] = glm::vec2(1, 1);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, shader);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, shader);
	texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, shader);
	texs[0].loadFromFile("images/Hud/d.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	texs[1].loadFromFile("images/Hud/crojo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].setMagFilter(GL_NEAREST);
	texs[2].loadFromFile("images/Hud/d_left.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[2].setMagFilter(GL_NEAREST);

}

void Hud::update(int deltaTime) {
	currentTime += deltaTime;
	if (personaje == 1) lifeInBarra = (float)((currentVida * 0.215f) / 100.f);
	else lifeInBarra = (float)((currentVida * -0.215f) / 100.f);
}

void Hud::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("projection", glm::ortho(0.f, float(640), float(480 - 1), 0.f));
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (personaje == 1) {
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview = glm::translate(modelview, glm::vec3(54.9f, 50.4f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(lifeInBarra, 0.042f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview);
		texQuad[1]->render(texs[1]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview = glm::translate(modelview, glm::vec3(20.f, -5.f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 0.3f));
		texProgram.setUniformMatrix4f("modelview", modelview);
		texQuad[0]->render(texs[0]);
	}

	else {
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview = glm::translate(modelview, glm::vec3(640 - 59.f, 50.4f ,0.f));
		modelview = glm::scale(modelview, glm::vec3(lifeInBarra, 0.042f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview);
		texQuad[1]->render(texs[1]);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
		modelview = glm::translate(modelview, glm::vec3(640.f- 216.f, -5.f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 0.3f));
		texProgram.setUniformMatrix4f("modelview", modelview);
		texQuad[2]->render(texs[2]);
	}

}

void Hud::changeLife(int life) {
	currentVida = life;
}