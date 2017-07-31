#include "Settings.h"

int Settings::_boardSize = 10;
float Settings::_soundVolume = 1.f;

Settings::Rule Settings::_GameRules = Settings::Rule::International;
bool Settings::_flyingKing = true;
bool Settings::_backwardEat = true;
bool Settings::_eatMaxPieces = true;

Settings::Player Settings::player1 = Settings::Player::Human;
Settings::Player Settings::player2 = Settings::Player::Human;

void
Settings::save()
{

}

void
Settings::load()
{

}
