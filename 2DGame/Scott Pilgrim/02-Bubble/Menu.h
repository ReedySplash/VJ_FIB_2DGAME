#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Scene.h"
#include <vector>

class Menu
{
public:
	Menu();
	~Menu();
	void init(bool musica);

private:
	bool musica;
};

#endif

