#include "MainMenu.h"
#include <glm/gtc/matrix_transform.hpp>



MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::init(bool music) {
	if (music) {
		//	mciSendString(TEXT("play sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3 repeat"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3 repeat"), NULL, 0, NULL);
	}
	else {
		//	mciSendString(TEXT("stop sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("stop sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3"), NULL, 0, NULL);
	}
	this->musica = music;
	currentTime = 0.0f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };//0,0
	glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(960.0f, 480.0f) };
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	
}

bool MainMenu::update(int deltaTime) {
	return true;
}

void MainMenu::render() {
	glm::mat4 modelview;

	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);

	//menuDash.render();
}
