#include "Menu.h"
#include <iostream>
#include <cmath>
#include <algorithm>


Menu::Menu()
{
}


Menu::~Menu()
{
}


void Menu::init(bool musica) {
	if (musica) {
		//	mciSendString(TEXT("play sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3 repeat"), NULL, 0, NULL);
		mciSendString(TEXT("play sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3 repeat"), NULL, 0, NULL);
	}
	else {
		//	mciSendString(TEXT("stop sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("stop sounds/SOUND/FileSelect-SuperMario64MusicExtended.mp3"), NULL, 0, NULL);
	}
	musica = musica;
}
