#ifndef __UTIL_H
#define __UTIL_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <time.h>

#include "glut.h"
#include "gl.h"

#pragma warning(disable:4996)
using namespace std;

/** Klasa z pomocniczymi narzedziami (np. funkcja wczytujaca bitmape z pliku dyskowego). 
*/
class CUTIL {
public:


	/** Wczytywanie bitmapy z pliku dyskowego, bitmapa moze byc wykorzystywana np. jako tekstura nakladana na obiekty lub zrodlo informacji o budowie sceny.
	@return Wskaznik na dane bitmapy.
	*/
	static unsigned char* LoadBitmapFile( char *filename, BITMAPINFOHEADER *bitmapInfoHeader ) {

		FILE *filePtr;
		BITMAPFILEHEADER bitmapFileHeader;
		unsigned char *bitmapImage;
		int	imageIdx = 0;

		filePtr = fopen(filename, "rb");
		if (filePtr == NULL)
			return NULL;

		fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
		fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

		fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

		bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

		if (!bitmapImage) {
			free(bitmapImage);
			fclose(filePtr);
			return NULL;
		}

		fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

		if (bitmapImage == NULL) {
			fclose(filePtr);
			return NULL;
		}

		/*for (imageIdx = 0; imageIdx < (int)bitmapInfoHeader->biSizeImage; imageIdx+=3) {
			tempRGB = bitmapImage[imageIdx];
			bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
			bitmapImage[imageIdx + 2] = tempRGB;
		}*/
		fclose(filePtr);

		return bitmapImage;
	}


	/** Funkcja rysuje szescian (podobnie jak glutSolidCube(), ale definiuje rowniez wektory normalne i koordynaty tekstury).
	*/
	static void drawBox( void ) {		
		
		//CGL blah;
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, blah.text1);

		glBegin(GL_QUADS);		// Draw The Cube Using quads
		 
		glNormal3f( 0, 1.0f, 0 );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Top)
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Top)
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
		 
		glNormal3f( 0, -1.0f, 0 );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Bottom)
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Bottom)

		glNormal3f( 0, 0, 1.0f );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Front)

		glNormal3f( 1.0f, 0, 0.0f );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Right)
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Right)
		 
		glNormal3f( -1.0f, 0, 0.0f );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Left)
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Left)
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
		
		glNormal3f( 0, 0, -1.0f );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Top Right Of The Quad (Back)
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Top Left Of The Quad (Back)
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Bottom Left Of The Quad (Back)
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Bottom Right Of The Quad (Back)	
		
		glEnd();			// End Drawing The Cube		

}


	/** Rysowanie tekstu na ekranie.
	@param x - wspolrzedna x tekstu
	@param y - wspolrzedna y tekstu
	@param z - wspolrzedna z tekstu
	@param font - rodzaj czcionki
	@param string - tekst, ktory ma byc narysowany 
	*/
	static void renderBitmapString( float x, float y, float z, void *font, char *string) {  
		char *c;
		glRasterPos3f( x, y, z );
		for (c=string; *c != '\0'; c++) {
			glutBitmapCharacter(font, *c);
		}
	}

	/** Wyswietlanie komunikatu w konsoli
	*/
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
	static void show_message( char* msg ) {
		printf( "%s\n", msg );
	}

	
	/** Zwraca aktualny czas systemowy w milisekundach
	*/
	static float getTime( void ) {
		return (float)clock() / (float)CLOCKS_PER_SEC * 1000;
	} 
	
	
	
};





#endif



