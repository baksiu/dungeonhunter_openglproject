#include "player.h"

void playerstats::addHealth(int liczba)
{
	health = health + liczba;
}
void enemystats::addDamage(int liczba)
{
	health = health - liczba;
}