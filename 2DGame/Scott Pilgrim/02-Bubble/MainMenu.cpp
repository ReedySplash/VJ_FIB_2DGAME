#include "MainMenu.h"



MainMenu::MainMenu()
{

}


MainMenu::~MainMenu()
{
	texProgram.free();
}

void MainMenu::init(bool music) {

	if (music) {
		mciSendString(TEXT("play sounds/SOUND/MenuTheme.mp3 repeat"), NULL, 0, NULL);
	}
	else {
		mciSendString(TEXT("stop sounds/SOUND/MenuTheme.mp3"), NULL, 0, NULL);
	}
	musica = music;
	currentTime = 0.0f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(620, 348.f) };

	initShaders();
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texs[0].loadFromFile("images/MainMenu_new.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[0].setMagFilter(GL_NEAREST);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

bool MainMenu::update(int deltaTime) {
	currentTime += deltaTime;
	return true;
}

void MainMenu::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);
}


void MainMenu::initShaders()
{
	Shader vShader, fShader;
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
	vShader.free();
	fShader.free();
}

