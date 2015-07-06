#include "conf.h"
 
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <time.h>

using namespace std;
 
#include "util.h"
#include "glut.h"
#include "gl.h"
#include "player.h"



int w1=880;
int h1=800;
 
void orthogonalStart(void) {
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, w1, 0, h1);
        glScalef(1, -1, 1);
        glTranslatef(0, -h1, 0);
        glMatrixMode(GL_MODELVIEW);
}
 
void orthogonalEnd(void) {
        glEnable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
}
 
void TextOnScreen(std::string s, int X, int Y)
{
        glRasterPos2i(X, Y);
        void * font = GLUT_BITMAP_TIMES_ROMAN_24;
        for (string::iterator i = s.begin(); i != s.end(); ++i)
        {
                char c = *i;
                glutBitmapCharacter(font, c);
        }
}