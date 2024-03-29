#ifndef _MENUOPTIONS_INCLUDE
#define _MENUOPTIONS_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <Windows.h>
#include <glm/gtc/matrix_transform.hpp>
#include "TexturedQuad.h"
#include "Text.h"
#include <iostream>
#include <vector>
#include "SLevelAPlayer.h"
#include "Instructions.h"
#include "ExtraMode.h"

#define CAMERA_WIDTH 1280
#define CAMERA_HEIGHT 720

class MenuOptions
{
public:
	MenuOptions();
	~MenuOptions();
	void init(bool musica);
	void update(int deltaTime);
	void render();
	void upOption();
	void downOption();
	void changeMusica();
	void changeCharLeft();
	void changeCharRight();
	void playGame();
	void showCredits();
	void showExtraMode();
	int getLevel();
	bool getMusic();
	int getPersonaje();

private:
	int currentTime;
	int opcion;
	bool musica;

	TexturedQuad *texQuad[3];
	Texture texs[2];
	ShaderProgram simpleTexProgram, texProgram;
	glm::mat4 projection;
	Text white, black;
	string musica_string[2];
	string text_music;
	bool play, instructions, extraMode_opt;
	SLevelAPlayer slevel;
	Instructions inst;
	ExtraMode extraMode;

	void initShaders();
};

#endif

