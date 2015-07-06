#include "conf.h"

#include <windows.h>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <conio.h>
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

struct list {
    int lvl;
	int kill;
	struct list *next;
} ;

void CGL::highscoresave(int score,int kill)
{
	string bufor = intTostr(score);
	string bufor2 = intTostr(kill);
	ofstream NowyPlik;
	NowyPlik.open("..\\resources\\highscores.txt",ios::app);
	if(NowyPlik.good() == true)
	{
		NowyPlik<<bufor<<" "<< bufor2<<endl;
	}
	else
	{
		cout << "Nie mozna zapisac statystyk do pliku" << endl;
	}
	NowyPlik.close();
}
bool CGL::highscoreload()
{
	int i = 0;
	ifstream NowyPlik;
	NowyPlik.open("..\\resources\\highscores.txt",ios::app);
	if( !NowyPlik.good() )
         return false;
    while( true ) //pêtla nieskoñczona
    {
        int a;
        int c;
        NowyPlik >> a >> c;
        if( NowyPlik.good() )
             wyswietlWynikiOrtho( a, c, i );
        else
             break;
		i=i+50;
		cout <<i<<endl;
    }
    return true;
}
string CGL::intTostr(int score)
{
	ostringstream ss;
	ss << score;
	string bufor = ss.str();
	return bufor;
}
string CGL::intTostr(float time)
{
	ostringstream ss;
	ss << time;
	string bufor = ss.str();
	return bufor;
}
void CGL::wyswietlWyniki(int a,int b)
{
	cout << "Zycie: " << a << "Zabici: " << b <<endl;
}
void CGL::wyswietlWynikiOrtho(int a,int b, int i)
{

	str = intTostr(a);
	str2 = intTostr(b);

	orthogonalStart();
	glColor3f(0.0f, 0.0f, 1.0f);
	TextOnScreen("Poziom lochu: ", 325, 350+i);
	TextOnScreen(str, 400, 350+i);
	TextOnScreen("Zabici: ", 475, 350+i);
	TextOnScreen(str2, 525, 350+i);
	orthogonalEnd();
}
void CGL::multipleEnemies(int scale)
{
			CEnemy* ce= new CEnemy();
			ce->x = 0.35;
			ce->y = 0.1;
			ce->dir = rotationE;
			ce->life = 10 * ((scale - 1)*(-1));
			ce->id = id;
			ce->time = 0;
			enemy_list.push_back( ce );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;

			CEnemy* ce1= new CEnemy();
			ce1->x = 0.25;
			ce1->y = 0.1;
			ce1->dir = rotationE;
			ce1->life = 10 * ((scale - 1)*(-1));
			ce1->id = id;
			ce1->time = 0;
			enemy_list.push_back( ce1 );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;

			CEnemy* ce2= new CEnemy();
			ce2->x = posXE;
			ce2->y = posYE+0.05;
			ce2->dir = rotationE;
			ce2->life = 10 * ((scale - 1)*(-1));
			ce2->id = id;
			ce2->time = 0;
			enemy_list.push_back( ce2 );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;

			CEnemy* ce3= new CEnemy();
			ce3->x = posXE-0.09;
			ce3->y = posYE-0.1;
			ce3->dir = rotationE;
			ce3->life = 10 * ((scale - 1)*(-1));
			ce3->id = id;
			ce3->time = 0;
			enemy_list.push_back( ce3 );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;

			CEnemy* ce4= new CEnemy();
			ce4->x = 0.85;
			ce4->y = 0.1;
			ce4->dir = rotationE;
			ce4->life = 10 * ((scale - 1)*(-1));
			ce4->id = id;
			ce4->time = 0;
			enemy_list.push_back( ce4 );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;

			CEnemy* ce5= new CEnemy();
			ce5->x = 0.9;
			ce5->y = 0.5;
			ce5->dir = rotationE;
			ce5->life = 10 * ((scale - 1)*(-1));
			ce5->id = id;
			ce5->time = 0;
			enemy_list.push_back( ce5 );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;

			CEnemy* ce6= new CEnemy();
			ce6->x = 0.65;
			ce6->y = 0.9;
			ce6->dir = rotationE;
			ce6->life = 10 * ((scale - 1)*(-1));
			ce6->id = id;
			ce6->time = 0;
			enemy_list.push_back( ce6 );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;

			CEnemy* ce7= new CEnemy();
			ce7->x = 0.8;
			ce7->y = 0.8;
			ce7->dir = rotationE;
			ce7->life = 10 * ((scale - 1)*(-1));
			ce7->id = id;
			ce7->time = 0;
			enemy_list.push_back( ce7 );
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;


}