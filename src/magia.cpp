#include "conf.h"

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "util.h"
#include "glut.h"
#include "gl.h"
#include "player.h"
#include "headers\Model_3DS.h"

void orthogonalEnd(void);
void orthogonalStart(void);
void TextOnScreen(std::string s,int X,int Y);

int CGL::fireball(int magic)
{
	if (magic == 0)
	{
		komunikat = "Nie posiadasz zwoju magii.";
		if(findState(STATE_POPUP))
		{
			state_list.remove(STATE_POPUP);
			t_waitk = 0;
		}
		state_list.push_back(STATE_WAIT_KOMUNIKAT);
		state_list.push_back(STATE_POPUP);
		magic = 0;
		return magic;
	}
	magic = 1;
	komunikat = "Wybrales kule ognia.";
	if(findState(STATE_POPUP))
	{
		state_list.remove(STATE_POPUP);
		t_waitk = 0;
	}
	state_list.push_back(STATE_WAIT_KOMUNIKAT);
	state_list.push_back(STATE_POPUP);
	return magic;
}
int CGL::icesicle(int magic)
{
	if (magic == 0)
	{
		komunikat = "Nie posiadasz zwoju magii.";
		if(findState(STATE_POPUP))
		{
			state_list.remove(STATE_POPUP);
			t_waitk = 0;
		}
		state_list.push_back(STATE_WAIT_KOMUNIKAT);
		state_list.push_back(STATE_POPUP);
		magic = 0;
		return magic;
	}
	magic = 2;
	komunikat = "Wybrales lodowy podmuch.";
	if(findState(STATE_POPUP))
	{
		state_list.remove(STATE_POPUP);
		t_waitk = 0;
	}
	state_list.push_back(STATE_WAIT_KOMUNIKAT);
	state_list.push_back(STATE_POPUP);
	return magic;
}