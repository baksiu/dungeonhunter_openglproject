
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

#define SCENE_FILE_NAME "../resources/mscene.bmp"


///////////////////////////////////////// utworzenie obiektu klasy CGL
CGL cgl;
playerstats player1;
enemystats enemy1;
playerequipment eq;
Model_3DS model;
Model_3DS model2;
Model_3DS model3;
Model_3DS model4;
Model_3DS model5;
Model_3DS model6;

///////////////////////////////////////// inicjalizacja srodowiska graficznego oraz zmiennych 
void CGL::init( void ) {

	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective( 75, 1.33/1.0, 0.01, 100 );
	gluLookAt( 0, 0, 4, 0, 0, 0, 0, 1, 0 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	tekstura = loadBMPtexture("../resources/wall3.bmp");
	tekstura_2 = loadBMPtexture("../resources/floor2.bmp");
	tekstura_3 = loadBMPtexture("../resources/floor4.bmp");
	tekstura_4 = loadBMPtexture("../resources/floor5.bmp");
	tekstura_5 = loadBMPtexture("../resources/hole.bmp");
	tekstura_6 = loadBMPtexture("../resources/hud.bmp");
	tekstura_7 = loadBMPtexture("../resources/stats.bmp");
	tekstura_8 = loadBMPtexture("../resources/kom2.bmp");
	tekstura_9 = loadBMPtexture("../resources/gameover.bmp");
	model.Load("../resources/ziombi.3DS");
	model2.Load("../resources/arrow.3DS");
	model3.Load("../resources/butla.3DS");
	model4.Load("../resources/bdoor.3DS");
	model5.Load("../resources/torch.3DS");
	model6.Load("../resources/paper.3DS");
	
	float global[4];
	SET_VEC4( global, 0.25f, 0.25f, 0.25f, 1.0f );
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global);

	// ustawienie parametrow zrodla swiatla, wlaczenie oswietlenia
	float vec[4];
	float ret[4];
	float mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,mat);
	SET_VEC4( vec, 0.55f, 0.95f, 0.07f, 1.0f );
	MAT4xVEC4(ret,mat,vec);
	glLightfv(GL_LIGHT0, GL_POSITION, ret );
	SET_VEC4( vec, 0.25f, 0.25f, 0.25f, 1.0f );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, vec);
	glLightfv(GL_LIGHT0, GL_EMISSION, vec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, vec); 
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 300.0f);
	
	float veca[4];
	SET_VEC4( veca, 0.1f, 0.1f, 0.07f, 1.0f );
	glLightfv(GL_LIGHT1, GL_POSITION, veca );
	SET_VEC4( veca, 0.04f, 0.04f, 0.04f, 1.0f );
	glLightfv(GL_LIGHT1, GL_DIFFUSE, veca);
	glLightfv(GL_LIGHT1, GL_AMBIENT, veca);
	glLightfv(GL_LIGHT1, GL_EMISSION, veca);
	glLightfv(GL_LIGHT1, GL_SPECULAR, veca);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 150.0f);

	float vecb[4];
	SET_VEC4( vecb, posX, posY, 0.06f, 1.0f );
	glLightfv(GL_LIGHT2, GL_POSITION, vecb );
	SET_VEC4( vecb, 0.1f, 0.1f, 0.1f, 1.0f );
	glLightfv(GL_LIGHT2, GL_DIFFUSE, vecb);
	glLightfv(GL_LIGHT2, GL_AMBIENT, vecb);
	glLightfv(GL_LIGHT2, GL_EMISSION, vecb);
	glLightfv(GL_LIGHT2, GL_SPECULAR, vecb);
	SET_VEC4( vecb, 0.0f, -1.0f, -1.0f, 1.0f );
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, vecb);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0f);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 150.0f);

	float vecc[4];
	glGetFloatv(GL_PROJECTION_MATRIX,mat);
	SET_VEC4( vecc, 0.2f, 0.8f, 0.07f, 1.0f );
	MAT4xVEC4(ret,mat,vecc);
	glLightfv(GL_LIGHT3, GL_POSITION, ret );
	SET_VEC4( vecc, 0.1f, 0.1f, 0.1f, 1.0f );
	glLightfv(GL_LIGHT3, GL_DIFFUSE, vecc);
	glLightfv(GL_LIGHT3, GL_AMBIENT, vecc);
	glLightfv(GL_LIGHT3, GL_EMISSION, vecc);
	glLightfv(GL_LIGHT3, GL_SPECULAR, vecc);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 300.0f);

	float vecd[4];
	glGetFloatv(GL_PROJECTION_MATRIX,mat);
	SET_VEC4( vecd,0.7, 0.025, 0.02f, 1.0f );
	MAT4xVEC4(ret,mat,vecd);
	glLightfv(GL_LIGHT4, GL_POSITION, ret );
	SET_VEC4( vecd, 0.25f, 0.025f, 0.25f, 1.0f );
	glLightfv(GL_LIGHT4, GL_DIFFUSE, vecd);
	glLightfv(GL_LIGHT4, GL_AMBIENT, vecd);
	glLightfv(GL_LIGHT4, GL_EMISSION, vecd);
	glLightfv(GL_LIGHT4, GL_SPECULAR, vecd);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 300.0f);
	
	float vece[4];
	glGetFloatv(GL_PROJECTION_MATRIX,mat);
	SET_VEC4( vece, 0.9f, 0.05f, 0.05f, 1.0f );
	MAT4xVEC4(ret,mat,vece);
	glLightfv(GL_LIGHT5, GL_POSITION, ret );
	SET_VEC4( vece, 0.05f, 0.05f, 0.05f, 1.0f );
	glLightfv(GL_LIGHT5, GL_DIFFUSE, vece);
	glLightfv(GL_LIGHT5, GL_AMBIENT, vece);
	glLightfv(GL_LIGHT5, GL_EMISSION, vece);
	glLightfv(GL_LIGHT5, GL_SPECULAR, vece);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 100.0f);

	float vecf[4];
	glGetFloatv(GL_PROJECTION_MATRIX,mat);
	SET_VEC4( vecf, 0.95f, 0.5f, 0.05f, 1.0f );
	MAT4xVEC4(ret,mat,vecf);
	glLightfv(GL_LIGHT6, GL_POSITION, ret );
	SET_VEC4( vecf, 0.1f, 0.1f, 0.1f, 1.0f );
	glLightfv(GL_LIGHT6, GL_DIFFUSE, vecf);
	glLightfv(GL_LIGHT6, GL_AMBIENT, vecf);
	glLightfv(GL_LIGHT6, GL_EMISSION, vecf);
	glLightfv(GL_LIGHT6, GL_SPECULAR, vecf);
	glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 300.0f);

	float vecg[4];
	glGetFloatv(GL_PROJECTION_MATRIX,mat);
	SET_VEC4( vecg, 0.03f, 0.15f, 0.05f, 1.0f );
	MAT4xVEC4(ret,mat,vecg);
	glLightfv(GL_LIGHT7, GL_POSITION, ret );
	SET_VEC4( vecg, 0.1f, 0.1f, 0.1f, 1.0f );
	glLightfv(GL_LIGHT7, GL_DIFFUSE, vecg);
	glLightfv(GL_LIGHT7, GL_AMBIENT, vecg);
	glLightfv(GL_LIGHT7, GL_EMISSION, vecg);
	glLightfv(GL_LIGHT7, GL_SPECULAR, vecg);
	glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 100.0f);

	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);
	glEnable(GL_LIGHTING);	


	// wlaczenie cieniowania Gouraud'a (smooth shading)
	glShadeModel( GL_SMOOTH ); 

	// ustawienie koloru tla
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f ); 

	// skasowanie bufora klawiatury
	for( int i=0; i < 256; i++ )
			cgl.keyStates[i] = false;

	// poczatkowe polozenie obiektu
	posX = 0.051;
	posY = 0.071;
	posZ = 0.5;
	isJump=false;
	rotationY = -90;
	posXE = 0.2;
	posYE = 0.73;
	posZE = 0.0;
	posXW = posX;
	posYW = posY;
	posZW = 0.03;
	rotation = 90;	
	posXOld = posX;
	posYOld = posY;
	posZOld = posZ;
	rotationOld = rotation;
	rotationW = rotation;
	widthMagic = 0.2f;
	dtOld = dt;
	rotationE = 180;
	obrot = 0.0f;
	wysokosc = 0.0024f;
	id = 1;
	komunikat1 = false;
	//i = 0;
	
	// odczytanie i wyswietlenie wersji OpenGL
	char* version = (char*)glGetString(GL_VERSION);
	printf("GL version: %s\n", version);	

	// odczytanie struktury sceny z zewnetrznego pliku (!!! dane bitmapy odczytane sa w formacie BGR888)
	newMap();

	//dodaje do listy przeciwników
	multipleEnemies(player1.lvlstat);

	// poczatkowe stany gry (! wazna jest kolejnosc stanow na liscie)
	state_list.push_back( STATE_DRAW_SCENE );
	state_list.push_back( STATE_DRAW_ENEMY );
	state_list.push_back( STATE_DRAW_OBJECT );
	state_list.push_back( STATE_NEW_LIGHT );
	state_list.push_back( STATE_NEW_LIGHT_2 );
	state_list.push_back( STATE_COLLISIONS_SCENE );
	state_list.push_back( STATE_COLLISIONS );
	state_list.push_back( STATE_MISSLE );
	state_list.push_back( STATE_HUD );
}


///////////////////////////////////////// glowna procedura przerysowania ekranu

bool is_first = true;

void CGL::display( void ) {

	if( is_first ) {
		t_old = CUTIL::getTime();
		is_first = false;
	}
	
	float t = CUTIL::getTime(); // aktualny czas
	float dt = t - t_old; // czas, ktory uplynal od poprzedniego wywolania display()
	t_old = t;
	 
	glClearDepth(1);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// obsluga klawiatury	
	keyOperations(); 
	
	// transformacja calej sceny
	glPushMatrix();	

	// zmiana widoku kamery
	glTranslatef( 0.0f, -0.035f,3.99f ); // przesuniecie korekcyjne	
	glRotatef( rotationY, 1, 0, 0 ); // pochylenie kamery (3PP)
	glRotatef( -rotation+90, 0, 0, 1 ); // obrot planszy zgodnie z obrotem gracza
	glTranslatef( -posX, -posY, -posZ );	// przesuniecie planszy do polozenia gracza
	///

	// glowna petla obslugujaca stany gry
	int idx;
	bool bb;
	list<CMissle*>::iterator it;
	list<CMissle*>::iterator ite;
	list<int> states = state_list;
	list<int>::iterator state;
	for( state = states.begin(); state != states.end(); ++state) {
					
		if(rotationY > 0 || rotationY < -180)
		{
			rotationY = -90;
		}
		if(!findState(STATE_MAGIC_ATTACK))
		{
			posXW = posX;
			posYW = posY;
			rotationW = rotation;
		}
		else
		{
			posXWOld = posXW;
			posYWOld = posYW;
			posZWOld = posZW;
			rotationWOld = rotationW;
		}
		bb = xy2mscene( posX, posY, idx );
		if( bb || (mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 255) ) 
		{
			newMap();
			player1.lvlstat--;
			enemy_list.clear();
			state_list.clear();
			state_list.push_back( STATE_DRAW_SCENE );
			state_list.push_back( STATE_DRAW_ENEMY );
			state_list.push_back( STATE_DRAW_OBJECT );
			state_list.push_back( STATE_NEW_LIGHT );
			state_list.push_back( STATE_COLLISIONS_SCENE );
			state_list.push_back( STATE_COLLISIONS );
			state_list.push_back( STATE_MISSLE );
			state_list.push_back( STATE_HUD );
			multipleEnemies(player1.lvlstat);

		}
		bb = xy2mscene( posX, posY, idx );
		if( bb || (mscene[idx] == 128 && mscene[idx+1] == 128 && mscene[idx+2] == 128) ) 
		{
			posX = posXOld;
			posY = posYOld;
		}
		bb = xy2mscene( posX, posY, idx );
		if( bb || (mscene[idx] == 255 && mscene[idx+1] == 0 && mscene[idx+2] == 0) ) 
		{
			
			mscene[idx]=0;
			player1.addHealth(3.5*(player1.lvlstat-1)*-1);
			if(findState(STATE_POPUP))
			{
				state_list.remove(STATE_POPUP);
				t_waitk = 0;
			}
			komunikat = "Podniosles eliksir zdrowia.";
			state_list.push_back(STATE_WAIT_KOMUNIKAT);
			state_list.push_back(STATE_POPUP);
		}
		bb = xy2mscene( posX, posY, idx );
		if( bb || (mscene[idx] == 255 && mscene[idx+1] == 0 && mscene[idx+2] == 255) ) 
		{
			mscene[idx]=0;
			mscene[idx+2]=0;
			eq.qntMagic1=eq.qntMagic1 + 1;
			komunikat = "Zdobyles zwoj magii.";
			state_list.push_back(STATE_WAIT_KOMUNIKAT);
			state_list.push_back(STATE_POPUP);
		}		
		switch( *state ) {

		
			case STATE_POPUP:
				str5 = komunikat;
			
				glLoadIdentity();
				glColor3f(0.55,0.55,0.55);


				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_8);
				orthogonalStart();
				glBegin(GL_QUADS);
					glTexCoord2f( 0.0f, 1.0f );
					glVertex2f(320, 125);
					glTexCoord2f( 1.0f, 1.0f );
					glVertex2f(545, 125);
					glTexCoord2f( 1.0f, 0.0f );
					glVertex2f(545, 325);
					glTexCoord2f( 0.0f, 0.0f );
					glVertex2f(320, 325);
				glEnd();
				orthogonalEnd();

				orthogonalStart();
				glColor3f(0.05,0.05,0.05);
				TextOnScreen(str5, 375, 225);
				orthogonalEnd();

				if(t_waitk > 3000)
				{
					t_waitk = 0;
					state_list.remove(STATE_WAIT_KOMUNIKAT);
					state_list.remove(STATE_POPUP);
				}
				break;
			///////////////////	obrot obiektu w lewo
			case STATE_HUD:

				str = intTostr(player1.lvlstat);
				str2 = intTostr(player1.health);
				str3 = intTostr(player1.killedstat);
				str4 = intTostr(eq.qntMagic1);
				glLoadIdentity();

				glColor3f(0.75,0.75,0.75);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_6);
				orthogonalStart();
				glBegin(GL_QUADS);
					glTexCoord2f( 0.0f, 1.0f );
					glVertex2f(0,0);
					glTexCoord2f( 1.0f, 1.0f );
					glVertex2f(880,0);
					glTexCoord2f( 1.0f, 0.0f );
					glVertex2f(880, 50);
					glTexCoord2f( 0.0f, 0.0f );
					glVertex2f(0, 50);
				glEnd();
				orthogonalEnd();

				orthogonalStart();
				glColor3f(0.75,0.75,0.75);
				TextOnScreen("Aktualny poziom lochu: ", 150, 30);
				TextOnScreen(str, 275, 30);
				TextOnScreen("Zycie: ", 325, 30);
				TextOnScreen(str2, 375, 30);
				TextOnScreen("Zabici: ", 450, 30);
				TextOnScreen(str3, 500, 30);
				TextOnScreen("Ilosc zwojow: ", 550, 30);
				TextOnScreen(str4, 650, 30);
				orthogonalEnd();
				break;

			//////////////////////// dodatkowe zrodlo swiatla
			case STATE_NEW_LIGHT:

				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorGray );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorGray );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorBlue );
				glPushMatrix();
				glTranslatef( 0.55f, 0.975f, 0.03f );
				glRotatef(-90,1,0,0);
				glRotatef(90,0,1,0);
				glRotatef(180,0,0,1);
				glScalef(0.01f,0.01f,0.01f);
				model5.Draw();
				glPopMatrix();
				float vec[4];
				SET_VEC4( vec, 0.55f, 0.92f, 0.05f, 1.0f );
				glLightfv(GL_LIGHT0, GL_POSITION, vec );

				glMaterialfv( GL_FRONT, GL_EMISSION, colorDarkRed );
				glPushMatrix();
				glTranslatef( 0.3f, 0.032f, 0.03f );
				glRotatef(0,1,0,0);
				glRotatef(-90,0,1,0);
				glRotatef(-90,0,0,1);
				glScalef(0.01f,0.01f,0.01f);
				model5.Draw();
				glPopMatrix();
				float veca[4];
				SET_VEC4( veca, 0.3f, 0.06f, 0.05f, 1.0f );
				glLightfv(GL_LIGHT1, GL_POSITION, veca );

				glMaterialfv( GL_FRONT, GL_EMISSION, colorDim );
				glPushMatrix();
				glTranslatef( posX, posY, posZ );
				glScalef(0.001f,0.001f,0.001f);
				glutSolidSphere( 1, 20, 20 );
				glPopMatrix();
				float vecb[4];
				SET_VEC4( vecb, posX, posY, 0.05f, 1.0f );
				glLightfv(GL_LIGHT2, GL_POSITION, vecb );
				
				glMaterialfv( GL_FRONT, GL_EMISSION, colorDarkRed );
				glPushMatrix();
				glTranslatef( 0.025f, 0.8f, 0.03f );
				glRotatef(-90,1,0,0);
				glRotatef(180,0,0,1);
				glScalef(0.01f,0.01f,0.01f);
				model5.Draw();
				glPopMatrix();

				float vecc[4];
				SET_VEC4( vecc, 0.055f, 0.8f, 0.05f, 1.0f );
				glLightfv(GL_LIGHT3, GL_POSITION, vecc );
				
				glMaterialfv( GL_FRONT, GL_EMISSION, colorDarkRed );
				glPushMatrix();
				glTranslatef( 0.9f, 0.027f, 0.03f );
				glRotatef(0,1,0,0);
				glRotatef(-90,0,1,0);
				glRotatef(-90,0,0,1);
				glScalef(0.01f,0.01f,0.01f);
				model5.Draw();
				glPopMatrix();
				float vece[4];
				SET_VEC4( vece, 0.9f, 0.05f, 0.05f, 1.0f );
				glLightfv(GL_LIGHT5, GL_POSITION, vece );

				glMaterialfv( GL_FRONT, GL_EMISSION, colorDarkRed );
				glPushMatrix();
				glTranslatef( 0.025f, 0.15f, 0.03f );
				glRotatef(-90,1,0,0);
				glRotatef(180,0,0,1);
				glScalef(0.01f,0.01f,0.01f);
				model5.Draw();
				glPopMatrix();
				float vecf[4];
				SET_VEC4( vecf, 0.05f, 0.15f, 0.05f, 1.0f );
				glLightfv(GL_LIGHT6, GL_POSITION, vecf );
				
				glMaterialfv( GL_FRONT, GL_EMISSION, colorDarkRed );
				glPushMatrix();
				glTranslatef( 0.25f, 0.66f, 0.03f );
				glRotatef(-90,1,0,0);
				glRotatef(90,0,1,0);
				glRotatef(180,0,0,1);
				glScalef(0.01f,0.01f,0.01f);
				model5.Draw();
				glPopMatrix();
				float vecg[4];
				SET_VEC4( vecg, 0.25f, 0.62f, 0.05f, 1.0f );
				glLightfv(GL_LIGHT7, GL_POSITION, vecg );
				
				break;

			case STATE_ROTATE_OBJECT_UP:
				rotationY = rotationY - dt * 0.12f * sin( -rotationY * 3.14f / 180.0f );
				state_list.remove( STATE_ROTATE_OBJECT_UP);
				break;
			case STATE_ROTATE_OBJECT_DOWN:
				rotationY = rotationY + dt *0.12f *sin( -rotationY * 3.14f / 180.0f );
				state_list.remove( STATE_ROTATE_OBJECT_DOWN );
				break;
			case STATE_ROTATE_OBJECT_LEFT:
				rotationOld = rotation;
				rotation = rotation + dt * 0.285f;
				state_list.remove( STATE_ROTATE_OBJECT_LEFT );
				break;

			///////////////////	obrot obiektu w prawo
			case STATE_ROTATE_OBJECT_RIGHT:
				rotationOld = rotation;
				rotation = rotation - dt * 0.285f;
				state_list.remove( STATE_ROTATE_OBJECT_RIGHT );
				break;

			case STATE_MOVE_OBJECT_RIGHT:
				posXOld=posX;
				posYOld=posY;
				posX = posX - dt * 0.00005f * sin( -rotation * 3.14f / 180.0f );
				posY = posY - dt * 0.00005f * cos( -rotation * 3.14f / 180.0f );

				bb = xy2mscene( posX, posY, idx );
				if(!isJump)
				{
					if( bb || (mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 0) || (mscene[idx] == 21 && mscene[idx+1] == 0 && mscene[idx+2] == 136 ) || (mscene[idx] == 14 && mscene[idx+1] == 201 && mscene[idx+2] == 255 )) 
					{
						posZ = posZ - dt * 0.5f;
						state_list.remove(STATE_DRAW_SCENE);
						state_list.remove(STATE_DRAW_ENEMY);
						state_list.remove(STATE_DRAW_OBJECT);
						state_list.push_back(STATE_GAMEOVER);
					}
				}

				state_list.remove( STATE_MOVE_OBJECT_RIGHT );
				break;
				
			case STATE_MOVE_OBJECT_LEFT:
				posXOld=posX;
				posYOld=posY;
				posX = posX + dt * 0.00005f * sin( -rotation * 3.14f / 180.0f );
				posY = posY + dt * 0.00005f * cos( -rotation * 3.14f / 180.0f );
				
				bb = xy2mscene( posX, posY, idx );
				if(!isJump)
				{
					if( bb || (mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 0) || (mscene[idx] == 21 && mscene[idx+1] == 0 && mscene[idx+2] == 136 ) || (mscene[idx] == 14 && mscene[idx+1] == 201 && mscene[idx+2] == 255 )) 
					{
						posZ = posZ - dt * 0.5f;
						state_list.remove(STATE_DRAW_SCENE);
						state_list.remove(STATE_DRAW_ENEMY);
						state_list.remove(STATE_DRAW_OBJECT);
						state_list.push_back(STATE_GAMEOVER);
					}
				}

				state_list.remove( STATE_MOVE_OBJECT_LEFT );
				break;
			///////////////////	ruch obiektu do przodu
			case STATE_MOVE_OBJECT_FORWARD:

				
				posXOld = posX;
				posYOld = posY;
				dtOld = dt;
				rotationOld = rotation;
				posX = posX + dt * 0.00015f * cos( rotation * 3.14f / 180.0f );
				posY = posY + dt * 0.00015f * sin( rotation * 3.14f / 180.0f );
				
				bb = xy2mscene( posX, posY, idx );
				if(!isJump)
				{
					if( bb || (mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 0) || (mscene[idx] == 21 && mscene[idx+1] == 0 && mscene[idx+2] == 136 ) || (mscene[idx] == 14 && mscene[idx+1] == 201 && mscene[idx+2] == 255 )) 
					{
						posZ = posZ - dt * 0.5f;
						state_list.remove(STATE_DRAW_SCENE);
						state_list.remove(STATE_DRAW_ENEMY);
						state_list.remove(STATE_DRAW_OBJECT);
						state_list.push_back(STATE_GAMEOVER);
					}
				}
				state_list.remove( STATE_MOVE_OBJECT_FORWARD );
				break;


			///////////////////	ruch obiektu do przodu
			case STATE_MOVE_OBJECT_BACKWARD:

				posXOld = posX;
				posYOld = posY;
				rotation = rotationOld;
				posX = posX - dt * 0.00015f * cos( rotation * 3.14f / 180.0f );
				posY = posY - dt * 0.00015f * sin( rotation * 3.14f / 180.0f );
				
				bb = xy2mscene( posX, posY, idx );
				if(!isJump)
				{
					if( bb || (mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 0) || (mscene[idx] == 21 && mscene[idx+1] == 0 && mscene[idx+2] == 136 ) || (mscene[idx] == 14 && mscene[idx+1] == 201 && mscene[idx+2] == 255 )) 
					{
						posZ = posZ - dt * 0.5f;
						state_list.remove(STATE_DRAW_SCENE);
						state_list.remove(STATE_DRAW_ENEMY);
						state_list.remove(STATE_DRAW_OBJECT);
						state_list.push_back(STATE_GAMEOVER);
					}
				}
				
				state_list.remove( STATE_MOVE_OBJECT_BACKWARD );
				break;

			/////////////////// kolizje
			case STATE_COLLISIONS:
				if( detectCollision( collisionTarget ) ) 
					pmaterial = MATERIAL_PLAYER_BLUE;
				else
					pmaterial = MATERIAL_PLAYER_RED;
				break;

			///////////////////	rysowanie obiektu
			case STATE_DRAW_OBJECT:
					for( ie = enemy_list.begin(); ie != enemy_list.end(); ie++) {
					bb1 = xy2mscene( (*ie)->x, (*ie)->y, idx1 );
					if( bb1 || (mscene[idx1] == 128 && mscene[idx1+1] == 128 && mscene[idx1+2] == 128) ) {
							if (findState(STATE_DRAW_ENEMY)){
								(*ie)->x = (*ie)->xOld;
								(*ie)->y = (*ie)->yOld;	
							}
						}
					}
				drawObject();
				break;					

			///////////////////	rysowanie obiektu
			case STATE_DRAW_SCENE:
				
				if(obrot > 180)
					obrot = 0;
				else
					obrot = obrot + dt*0.06f;

				drawScene();
				break;	
			/////////////////// rysowanie przeciwnika
			case STATE_DRAW_ENEMY:
				for( ie = enemy_list.begin(); ie != enemy_list.end(); ie++) {
					drawEnemy(*ie);
					(*ie)->xe = ((*ie)->x - posX);
					(*ie)->ye = ((*ie)->y - posY); 
					(*ie)->time = (*ie)->time + dt;
				}
				break;	

			////////////////// ruch, kolizje i kasowanie pociskow
			case STATE_MISSLE:
				
				////////// pociski przeciwnika
				for( ie = enemy_list.begin(); ie != enemy_list.end(); ie++) {
					{
						
						if ( (((*ie)->x)-(posX)<0.25)  && ((*ie)->y-(posY)<0.25) && (((posX)-((*ie)->x))<0.25)  && ((posY-(*ie)->y)<0.25))
						{
										enemyShoot();
										(*ie)->xOld = (*ie)->x;
										(*ie)->yOld = (*ie)->y;	
										(*ie)->x=(*ie)->x-((*ie)->x-posX)/50;
										(*ie)->y=(*ie)->y-((*ie)->y-posY)/50;
						}
					}
				};

				for( ite = missle_list_enemy.begin(); ite != missle_list_enemy.end(); ite++) {

					(*ite)->x = (*ite)->x - dt * 0.0005f * cos( (*ite)->dir * 3.14f / 180.0f );
					(*ite)->y = (*ite)->y - dt * 0.0005f * sin( (*ite)->dir * 3.14f / 180.0f );

					// kolizje pocisku ze scianami planszy
					bb = xy2mscene( (*ite)->x, (*ite)->y, idx );
					if( bb || (mscene[idx] == 255 && mscene[idx+1] == 255 && mscene[idx+2] == 255) ) {
						delete (*ite);
						missle_list_enemy.erase( ite );
						break;
					}

					////////////////// zestrzeliwanie gracza przez przeciwnika
					for( ie = enemy_list.begin(); ie != enemy_list.end(); ie++) {
					if (((((*ite)->x)-(posX))<0.01)  && ((*ite)->y-(posY)<0.01)	&& (((posX)-((*ite)->x))<0.01)  && ((posY-(*ite)->y)<0.01))
						{
							if ((*ite)!=0)
							{
								if (player1.health > 10){
									player1.health = player1.health - 2*(player1.lvlstat-1)*-1;
									(*ite)->x=-1;
									(*ite)->y=-1;
								}
								else
								{
									(*ite)->x=-1;
									(*ite)->y=-1;
									enemy_list.clear();
									state_list.remove(STATE_DRAW_SCENE);
									state_list.remove(STATE_DRAW_ENEMY);
									state_list.remove(STATE_DRAW_OBJECT);
									state_list.push_back(STATE_GAMEOVER);
								}
							}
							break;
					}
					}

					// skasowanie pocisku po przekroczeniu granic planszy 
					if( (*ite)->x < 0 || (*ite)->x > 1 || (*ite)->y < 0 || (*ite)->y > 1 ) 
					{
						delete (*ite);
						missle_list_enemy.erase( ite );
						break;
					}
					else
					{
						drawMissle2( *ite );
					}

				}
				//////////////////pociski gracza

				for( it = missle_list.begin(); it != missle_list.end(); it++) {

					(*it)->x = (*it)->x + dt * 0.0005f * cos( (*it)->dir * 3.14f / 180.0f );
					(*it)->y = (*it)->y + dt * 0.0005f * sin( (*it)->dir * 3.14f / 180.0f );

					// kolizje pocisku ze scianami planszy
					bb = xy2mscene( (*it)->x, (*it)->y, idx );
					if( bb || (mscene[idx] == 0 && mscene[idx+1] == 0 && mscene[idx+2] == 255) ) {
						mscene[idx] = 0;
						mscene[idx+1] = 0;
						mscene[idx+2] = 0;
						delete (*it);
						missle_list.erase( it );
						break;
					}
					//
					if( bb || (mscene[idx] == 255 && mscene[idx+1] == 255 && mscene[idx+2] == 255) ) {
						delete (*it);
						missle_list.erase( it );
						break;
					}
					////////////////
					if ( (((*it)->x)-(posX) > 0.25)  || ((*it)->y-(posY) > 0.25) || ((posX-((*it)->x)) > 0.25)  || ((posY-(*it)->y)>0.25)) 
					{
						if ((*ie)!=0)
						{
							delete (*it);
							missle_list.erase( it );
							break;
						}
					}
					// kolizje przeciwników z pociskami - zestrzewiwanie przeciwników
					for( ie = enemy_list.begin(); ie != enemy_list.end(); ie++)
					{
						if ( (((((*it)->x)-((*ie)->x))<0.01)  && ((*it)->y-(*ie)->y)<0.01) && (((((*ie)->x)-((*it)->x))<0.01)  && ((*ie)->y-(*it)->y)<0.01)) 
						{
							if ((*ie)!=0 && (*it)!=0)
							{
								if ((*ie)->life > 10){
									(*ie)->life = (*ie)->life - 10;
									
									(*it)->x=-1;
									(*it)->y=-1;
								}
								else
								{
									player1.killedstat++;
									delete (*ie);
									enemy_list.erase( ie );
									(*it)->x=-1;
									(*it)->y=-1;
								}
							}
							break;
						}
					
					};
					// skasowanie pocisku po przekroczeniu granic planszy 
					if( (*it)->x < 0 || (*it)->x > 1 || (*it)->y < 0 || (*it)->y > 1 ) {
						delete (*it);
						missle_list.erase( it );
						break;
					}
					else
						drawMissle( *it );
				}
				break;

			case STATE_MAGIC_ATTACK:
					
					if(eq.idMagic == 0 || eq.qntMagic1 == 0)
					{
						state_list.remove(STATE_MAGIC_ATTACK);
						break;
					}
					drawMagic(eq.idMagic);
					posXW = posXW + dt * 0.00015f * cos( rotationW * 3.14f / 180.0f );
					posYW = posYW + dt * 0.00015f * sin( rotationW * 3.14f / 180.0f );
					expX = posXW;
					expY = posYW;
					if (eq.idMagic == 2)
					{
						posZW = (sin(jump*3.14/180)/64);
						jump = jump + dt * 1/4;					
					}
					bb = xy2mscene( posXW, posYW, idx );
					if( bb || (mscene[idx] == 255 && mscene[idx+1] == 255 && mscene[idx+2] == 255) ) {
						
						state_list.remove(STATE_MAGIC_ATTACK);
						glDisable(GL_LIGHT4);
						eq.qntMagic1--;
						jump = 0;
						state_list.push_back(STATE_EXPLOSION);
						break;
					}
					/////kolizja magii z przeciwnikiem
					for( ie = enemy_list.begin(); ie != enemy_list.end(); ie++)
					{
						if ( ((((posXW)-((*ie)->x))<0.02)  && (posYW-(*ie)->y)<0.02) &&	(((((*ie)->x)-(posXW)<0.02)  && ((*ie)->y-posYW<0.02))))
						{
							if ((*ie)!=0)
							{
								if ((*ie)->life > 10)
								{
									(*ie)->life = (*ie)->life - 30;
									state_list.push_back(STATE_EXPLOSION);
								}
								else
								{
									state_list.push_back(STATE_EXPLOSION);
									player1.killedstat++;
									delete (*ie);
									enemy_list.erase( ie );
								}
								state_list.remove(STATE_MAGIC_ATTACK);
								glDisable(GL_LIGHT4);
								eq.qntMagic1--;
							}
							break;
						}
					};
				break;

			////////////////// ruch pociskow
			case STATE_WAIT:
				t_wait = t_wait + dt;
				break;
			
			case STATE_WAIT_KOMUNIKAT:
				t_waitk = t_waitk + dt;
				break;

			case JUMP:
				if(!isJump)
					isJump=true;
				posZOld = posZ;
				posXOld = posX;
				posYOld = posY;
				posZ = (sin(jump*3.14/180)/32);
				jump = jump + dt * 1/4;
				posX = posX + dt * 0.00001f * cos( rotation * 3.14f / 180.0f );
				posY = posY + dt * 0.00001f * sin( rotation * 3.14f / 180.0f );
				if (jump >= 180)
				{
					posZ = 0.0;
					jump = 0.0;
					isJump=false;
					state_list.remove(JUMP);
				}
				bb = xy2mscene( posX, posY, idx );
				if(!isJump)
				{
					if( bb || (mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 0) || (mscene[idx] == 21 && mscene[idx+1] == 0 && mscene[idx+2] == 136 ) || (mscene[idx] == 14 && mscene[idx+1] == 201 && mscene[idx+2] == 255 )) 
					{
						posZ = posZ - dt * 0.5f;
						state_list.remove(STATE_DRAW_SCENE);
						state_list.remove(STATE_DRAW_ENEMY);
						state_list.remove(STATE_DRAW_OBJECT);
						state_list.push_back(STATE_GAMEOVER);
					}
				}
				break;

			case STATE_GAMEOVER :

				glLoadIdentity();
				glColor3f(0.55,0.55,0.55);


				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_9);
				orthogonalStart();
				glBegin(GL_QUADS);
					glTexCoord2f( 0.0f, 1.0f );
					glVertex2f(0, 0);
					glTexCoord2f( 1.0f, 1.0f );
					glVertex2f(880, 0);
					glTexCoord2f( 1.0f, 0.0f );
					glVertex2f(880, 800);
					glTexCoord2f( 0.0f, 0.0f );
					glVertex2f(0, 800);
				glEnd();
				orthogonalEnd();

				str = intTostr(player1.lvlstat);
				str3 = intTostr(player1.killedstat);
				str4 = intTostr(((player1.lvlstat-2)*(player1.killedstat)*-1*17));

				orthogonalStart();
				glColor3f(0.75,0.75,0.75);
				TextOnScreen("Osiagniety poziom lochu: ", 150+100, 600);
				TextOnScreen(str, 275+100, 600);
				TextOnScreen("Zabici: ", 325+100, 600);
				TextOnScreen(str3, 375+100, 600);
				TextOnScreen("Wynik: ", 450+100, 600);
				TextOnScreen(str4, 500+100, 600);
				orthogonalEnd();

			case STATE_EXPLOSION :
				if (grow > 0.2f)
				{
					state_list.remove(STATE_EXPLOSION);
					grow = 0.0f;
				}
				drawExplosion();
				grow = grow + 0.01f;
				
				break;

		}
	}
	glPopMatrix();

	// wyswietlenie tylniego ekranu
	glutSwapBuffers(); 
	
	// wymuszenie przerysowania podczas nastêpnej synchronizacji ekranu
	glutPostRedisplay(); 
}

///////////////////////////////////////// rysowanie obiektu
void CGL::drawMissle( CMissle* cm ) {


	setMaterial( MATERIAL_WALL_GRAY );

	glPushMatrix();
	glTranslatef( cm->x, cm->y, 0.02f );
	glRotatef(cm->dir - 90, 0.0f, 0.0f, 1.0f );
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f );

	glScalef( 0.02f, 0.02f, 0.02f );	

	if( findState( STATE_COLLISIONS ) ) {
		glGetFloatv( GL_MODELVIEW_MATRIX, collisionTargetBullet.m );
		collisionTargetBullet.r = 0.005f;
	}
	model2.Draw();
	glPopMatrix();

}
void CGL::drawMissle2( CMissle* cm ) {


	setMaterial( MATERIAL_PLAYER_BLUE );

	glPushMatrix();
	glTranslatef( cm->x, cm->y, 0.02f );
	glRotatef(cm->dir, 0.0f, 0.0f, 1.0f );
	glScalef( 0.002f, 0.002f, 0.002f );	

	if( findState( STATE_COLLISIONS ) ) {
		glGetFloatv( GL_MODELVIEW_MATRIX, collisionTargetBullet.m );
		collisionTargetBullet.r = 0.005f;
	}
	glutSolidSphere(1,50,50);
	glPopMatrix();

}
void CGL::enemyShoot() {

		if( (*ie)->time > t_waite_time ){
	
		CMissle* cm = new CMissle();
		cm->x = (*ie)->x;
		cm->y = (*ie)->y;
		cm->dir = atan2((*ie)->ye,(*ie)->xe)*180/3.14f;
		missle_list_enemy.push_back( cm );

		// kolejny pocisk bedzie mozna utworzyc po 250 [msec]
		(*ie)->time = 0;
		t_waite_time = 2000;
		}
}
void CGL::drawEnemy( CEnemy* ce ) {

	setMaterial( pmaterial );

	glPushMatrix();
	glTranslatef( ce->x, ce->y, -0.06f );
	glRotatef(atan2(ce->ye,ce->xe)*180/3.14f,0.0f,0.0f,1.0f);
	glRotatef( ce->dir, 0.0f, 0.0f, 1.0f );
	glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	glRotatef( 90.0f, 0.0f, 1.0f, 0.0f );
	glScalef( 0.0005f, 0.0005f, 0.0005f );

	if (findState (STATE_COLLISIONS)){
		addCollision(0.009f);
	}

	model.Draw();
	glPopMatrix();
}

void CGL::drawExplosion() {

	setMaterial( MATERIAL_WALL_GRAY );

	glPushMatrix();
	glTranslatef( expX, expY, 0.01f );
	glScalef( grow, grow, grow );	
	glutSolidCube(1);
	glPopMatrix();


}
void CGL::drawMagic(int id)
{
	if (id == 1)
	{
		glMaterialfv( GL_FRONT, GL_EMISSION, colorDarkRed );
		setMaterial( MATERIAL_PLAYER_RED );
		glPushMatrix();
		glTranslatef( posXW, posYW, 0.02f );
		glRotatef( 0.0, 0.0f, 0.0f, 1.0f );
		glScalef( 0.007f, 0.007f, 0.007f );	

		if( findState( STATE_COLLISIONS ) ) {
			glGetFloatv( GL_MODELVIEW_MATRIX, collisionTargetBullet.m );
			collisionTargetBullet.r = 0.025f;
		}
		
		glutSolidSphere(1,50,50);
		glPopMatrix();
		
		float vecd[4];
		SET_VEC4( vecd, 0.7f, 0.425f, 0.25f, 1.0f );
		glLightfv(GL_LIGHT4, GL_DIFFUSE, vecd);
		glLightfv(GL_LIGHT4, GL_AMBIENT, vecd);
		glLightfv(GL_LIGHT4, GL_EMISSION, vecd);
		glLightfv(GL_LIGHT4, GL_SPECULAR, vecd);
		glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 300.0f);
		SET_VEC4( vecd, posXW, posYW, 0.02f, 1.0f );
		glLightfv(GL_LIGHT4, GL_POSITION, vecd );
		glEnable(GL_LIGHT4);
	}
	if (id == 2)
	{
		setMaterial( MATERIAL_WALL_GRAY );
		glPushMatrix();
		glTranslatef( posXW-0.03, posYW, posZW + 0.03);
		glRotatef( rotationW, 0.0f, 0.0f, 1.0f );
		glScalef( 0.01f,  0.01f, 0.01f );	

		if( findState( STATE_COLLISIONS ) ) {
			glGetFloatv( GL_MODELVIEW_MATRIX, collisionTargetBullet.m );
			collisionTargetBullet.r = 0.025f;
		}
		glutWireTetrahedron();
		glPopMatrix();

		setMaterial( MATERIAL_WALL_GRAY );
		glPushMatrix();
		glTranslatef( posXW+0.03, posYW, posZW+0.03 );
		glRotatef( rotationW, 0.0f, 0.0f, 1.0f );
		glScalef( 0.01f, 0.01f, 0.01f );	

		if( findState( STATE_COLLISIONS ) ) {
			glGetFloatv( GL_MODELVIEW_MATRIX, collisionTargetBullet.m );
			collisionTargetBullet.r = 0.025f;
		}
		glutWireTetrahedron();
		glPopMatrix();
		
		float vecd[4];
		SET_VEC4( vecd, 0.05f, 0.425f, 0.75f, 1.0f );
		glLightfv(GL_LIGHT4, GL_DIFFUSE, vecd);
		glLightfv(GL_LIGHT4, GL_AMBIENT, vecd);
		glLightfv(GL_LIGHT4, GL_EMISSION, vecd);
		glLightfv(GL_LIGHT4, GL_SPECULAR, vecd);
		glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 300.0f);
		SET_VEC4( vecd, posXW, posYW, 0.02f, 1.0f );
		glLightfv(GL_LIGHT4, GL_POSITION, vecd );
		glEnable(GL_LIGHT4);
	}
}
void CGL::drawObject( void ) {

	
	setMaterial( MATERIAL_PLAYER_RED );

	glPushMatrix();
	glTranslatef( posX, posY, posZ );
	glRotatef( rotation, 0.0f, 0.0f, 1.0f );
	glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	glScalef( 0.01f, 0.01f, 0.01f );	

	if( findState( STATE_COLLISIONS ) ) {
		glGetFloatv( GL_MODELVIEW_MATRIX, collisionTarget.m );
		collisionTarget.r = 0.025f;
	}
	glPopMatrix();
}



///////////////////////////////////////// rysowanie obiektow na scenie w oparciu o dane bitmapy
void CGL::drawScene( void ) {

	if( findState( STATE_COLLISIONS ) )
	{
		collision_list.clear(); // skasowanie listy kolizji
		collision_list2.clear();
		collision_list3.clear();
	}		
	glPushMatrix();
	//loadBMPtexture("../resources/texture.bmp");
	for( int c = 0; c < mscene_height; c++ ) {
		for( int w = 0; w < mscene_width; w++ ) {

			int idx = xy2idx( w, c );

			if( mscene[idx] == 255 && mscene[idx+1] == 255 && mscene[idx+2] == 255 ) { // biale elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, 0.03f );
				//glRotatef(90,1,0,0);
				glScalef( 1.3f/(float)mscene_width-0.015f, 1.2f/(float)mscene_height-0.015f, 2.5f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura);
				//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				if( findState(STATE_COLLISIONS) ) {
					addCollision( 0.015f );
				}
				glPopMatrix();
			}
			if( mscene[idx] == 192 && mscene[idx+1] == 192 && mscene[idx+2] == 192 ) { // biale elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, 0.03f );
				glRotatef(90,0,0,1);
				glScalef( 1.3f/(float)mscene_width-0.015f, 1.2f/(float)mscene_height-0.015f, 2.5f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				if( findState(STATE_COLLISIONS) ) {
					addCollision( 0.015f );
				}
				glPopMatrix();
			}
			if( mscene[idx] == 0 && mscene[idx+1] == 0 && mscene[idx+2] == 0 ) { // czarne elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_2);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
				/*
				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, 0.08f );
				glRotatef(90,1,0,0);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.05f/(float)mscene_height-0.015f, 1.5f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_2);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();*/
			}
			if( mscene[idx] == 128 && mscene[idx+1] == 128 && mscene[idx+2] == 128 ) { // szare elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				glScalef( 1.295f/(float)mscene_width-0.015f, 0.001f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_3);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if( mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 0 ) { // zielone elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );

				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				//glRotatef(-90,1,0,1);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_5);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if( mscene[idx] == 232 && mscene[idx+1] == 162 && mscene[idx+2] == 0 ) { // zielone elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(-90,1,0,0);

				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_5);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}

			if( mscene[idx] == 14 && mscene[idx+1] == 201 && mscene[idx+2] == 255 ) { // zielone elementy

				// kolor obiektu

				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				glRotatef(180,0,0,1);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_5);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if( mscene[idx] == 21 && mscene[idx+1] == 0 && mscene[idx+2] == 136 ) { // zielone elementy

				// kolor obiektu

				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_5);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if( mscene[idx] == 0 && mscene[idx+1] == 0 && mscene[idx+2] == 255 ) { // czerwone elementy

				// kolor obiektu
			/*	setMaterial( MATERIAL_PLAYER_RED );

			
				xe2 = ((float)w/(float)mscene_width + 0.5f/(float)mscene_width) - posX;
				ye2 = ((float)c/(float)mscene_height + 0.5f/(float)mscene_height) - posY;

				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.04f );
				glRotatef(atan2(ye2,xe2)*180/3.14, 0.0f, 0.0f, 1.0f );
				glRotatef( -90.0f, 0.0f, 0.0f, 1.0f );
				glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
				glScalef( 0.0005f, 0.0005f, 0.0005f );			
				model.Draw();
				if( findState(STATE_COLLISIONS) ) {
					addCollision( 0.001f );
				}
				glPopMatrix();*/

				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_2);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if( mscene[idx] == 255 && mscene[idx+1] == 0 && mscene[idx+2] == 0 ) { // niebieskie elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );
				//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.005f );
				glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
				glRotatef(obrot,0,1,0);
				glScalef( 0.0051f,0.0051f,0.0051f );	
				model3.Draw();
				glPopMatrix();
				//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

								
				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_2);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if( mscene[idx] == 255 && mscene[idx+1] == 0 && mscene[idx+2] == 255 ) { // niebieskie elementy


				// kolor obiektu
				setMaterial( MATERIAL_WALL_GRAY );
				//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, 0.0035f );
				glRotatef(-90,1,1,0);
				glScalef( 0.000051, 0.000051, 0.000051 );	
				model6.Draw();
				glPopMatrix();
			//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				setMaterial( MATERIAL_WALL_GRAY );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width , (float)c/(float)mscene_height + 0.5f/(float)mscene_height, -0.02f );
				glRotatef(90,1,0,0);
				glScalef( 1.3f/(float)mscene_width-0.015f, 0.01f/(float)mscene_height-0.015f, 1.18f/(float)mscene_width-0.011f );		
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,tekstura_2);
				CUTIL::drawBox();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if( mscene[idx] == 0 && mscene[idx+1] == 255 && mscene[idx+2] == 255 ) { // zolte elementy

				// kolor obiektu
				setMaterial( MATERIAL_WALL_YELLOW );
				//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				glPushMatrix();
				glTranslatef( (float)w/(float)mscene_width + 0.5f/(float)mscene_width, (float)c/(float)mscene_height + 0.5f/(float)mscene_height-0.011f, -0.005f );
				glRotatef(90.0f,0.0f,0.0f,1.0f);
				glScalef( 0.00024f,0.0002f,0.0002f );			
				model4.Draw();
				glPopMatrix();
				//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			}
		}
	}
	glPopMatrix();
}
void CGL::drawEnemy( void ) {

	xe = (posXE - posX);
	ye = (posYE - posY);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	setMaterial( MATERIAL_PLAYER_RED );

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glPushMatrix();
	glTranslatef( posXE, posYE, -0.06f );
	glRotatef( atan2(ye,xe)*180/3.14, 0.0f, 0.0f, 1.0f );
	glRotatef( -90.0f, 0.0f, 0.0f, 1.0f );
	glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	glScalef( 0.0005f, 0.0005f, 0.0005f );	
	if( findState( STATE_COLLISIONS ) ) {
		addCollisionEnemy( 0.005f );
	}
	model.Draw();
	glPopMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

///////////////////////////////////////// obsluga klawiatury

void CGL::keyUp( unsigned char key,int a,int b ) {
	
	keyStates[key] = false;	
}

void CGL::keyPress( unsigned char key,int a,int b ) {

	keyStates[key] = true;
}
	
void CGL::keyOperations( void ) {	
	
	if ( keyStates[27] ) {
		highscoresave(player1.lvlstat,player1.killedstat);
		exit(0);
	}
	if ( keyStates['p'] ) {
		if (findState(STATE_DRAW_SCENE)) {
			CEnemy* ce= new CEnemy();
			ce->x = posXE;
			ce->y = posYE;
			ce->dir = rotationE;
			ce->life = 100 * player1.lvlstat * -0.5;
			ce->id = id;
			ce->time = 0;
			enemy_list.push_back( ce );
			CGL::keyUp ('p',0,0);
			cout << "SPAWN PRZECIWNIKA NR "<< id <<endl;
			id = id + 1;
			posXE = posXE + 0.2f;
			
		}
	}
	// obrot obiektu w lewo
	if ( keyStates['a'] ) {
		if (!findState(STATE_MOVE_OBJECT_LEFT)) {
			state_list.push_front( STATE_MOVE_OBJECT_LEFT );	
		}
	}

	// obrot obiektu w prawo
	if ( keyStates['d'] ) {
		if (!findState(STATE_MOVE_OBJECT_RIGHT)) {
			state_list.push_front( STATE_MOVE_OBJECT_RIGHT );	
		}
	}

	// ruch obiektu do przodu
	if ( keyStates['w'] ) {
		if (!findState(STATE_MOVE_OBJECT_FORWARD)) {
			state_list.push_front( STATE_MOVE_OBJECT_FORWARD );	
		}
	}
	// ruch obiektu do ty³u
	if ( keyStates['s'] ) {
		if (!findState(STATE_MOVE_OBJECT_BACKWARD)) {
			state_list.push_front( STATE_MOVE_OBJECT_BACKWARD );	
		}
	}
	// JUMP!
	if ( keyStates[' '] ) {
		if (!findState(JUMP)) {
			state_list.push_front(JUMP);	
		}
	}
	if ( keyStates['x'] ) {

		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,tekstura_7);
		orthogonalStart();
		glColor3f(0.75,0.75,0.75);
		glBegin(GL_QUADS);
			glTexCoord2f( 0.0f, 1.0f );
			glVertex2f(150, 160);
			glTexCoord2f( 1.0f, 1.0f );
			glVertex2f(730, 160);
			glTexCoord2f( 1.0f, 0.0f );
			glVertex2f(730, 750);
			glTexCoord2f( 0.0f, 0.0f );
			glVertex2f(150, 750);
		glEnd();
		orthogonalEnd();
		highscoreload();
	}
	if ( keyStates['1'] ) {
		eq.idMagic = fireball(eq.qntMagic1);
	}
	if ( keyStates['2'] ) {
		eq.idMagic = icesicle(eq.qntMagic1);
	}

}

// obs³uga myszki

void CGL::myszka(int button, int state, int x, int y){

	// walka
	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) 
	{
			CMissle* cm = new CMissle();
			cm->x = posX;
			cm->y = posY;
			cm->dir = rotation;
			missle_list.push_back( cm );
	}

	//// magia
	if (button == GLUT_RIGHT_BUTTON && state==GLUT_DOWN) 
	{
		if (!findState(STATE_MAGIC_ATTACK)) {
			state_list.push_front( STATE_MAGIC_ATTACK );	
		}
	}
}
void CGL::myszkaRuch(int x, int y){

	static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	int dx = x - width/2;
    int dy = y - height/2;

    if(dx < 0) {
		if (!findState(STATE_ROTATE_OBJECT_LEFT)) {
			state_list.remove( STATE_ROTATE_OBJECT_RIGHT );
			state_list.push_front( STATE_ROTATE_OBJECT_LEFT );	
		}
    }

    if(dx > 0) {
        if (!findState(STATE_ROTATE_OBJECT_RIGHT)) {
			state_list.remove( STATE_ROTATE_OBJECT_LEFT );
			state_list.push_front( STATE_ROTATE_OBJECT_RIGHT );	
		}
    }
	if(dy < 0) {
		if (!findState(STATE_ROTATE_OBJECT_UP)) {
			state_list.remove( STATE_ROTATE_OBJECT_DOWN );
			state_list.push_front( STATE_ROTATE_OBJECT_UP );	
		}
    }
    if(dy > 0) {
        if (!findState(STATE_ROTATE_OBJECT_DOWN)) {
			state_list.remove( STATE_ROTATE_OBJECT_UP );
			state_list.push_front( STATE_ROTATE_OBJECT_DOWN );	
		}
    }
	glutWarpPointer(width/2, height/2);
    just_warped = true;
}






