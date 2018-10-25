#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE

#include "ShaderProgram.h"


class Hud
{
public:
	Hud();
	~Hud();
	void init(int person, ShaderProgram &shader);
	void update(int deltaTime);
	void render();
	void changeLife(int life);

private:
	int personaje;
	ShaderProgram TextureProgram;
};

#endif
