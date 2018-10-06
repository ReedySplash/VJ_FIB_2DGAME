#include <iostream>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <vector>
#include "Scene.h"
#include <windows.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#pragma once
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void init(bool music);
	bool update(int deltTime);
	void render();


private:
	bool musica;
	float currentTime;
	ShaderProgram simpleTexProgram;
	ShaderProgram simpleTexProgram;
	glm::mat4 projection;
	
};

