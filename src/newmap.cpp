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

using namespace std;

#include "util.h"
#include "glut.h"
#include "gl.h"
#include "player.h"

void CGL::newMap() {
						#define SCENE_FILE_NAME "../resources/mscene.bmp"
						BITMAPINFOHEADER bitmapInfoHeader;
						mscene = CUTIL::LoadBitmapFile( SCENE_FILE_NAME, &bitmapInfoHeader );
						if( mscene == NULL ) {
							printf( "ERROR: cannot open input file with the scene data\n" );
							exit(1);
						}
						mscene_width = (int)bitmapInfoHeader.biWidth;
						mscene_height = (int)bitmapInfoHeader.biHeight;
						mscene_line_length = (int)(bitmapInfoHeader.biSizeImage / mscene_height );
						printf( "bitmap size: %d,%d (line length:%d, size:%d (%d))\n", mscene_width, mscene_height, mscene_line_length, bitmapInfoHeader.biSizeImage, (mscene_width*mscene_height*3) );
						posX = 0.085;
						posY = 0.051;
						posZ = 0.0;
						posXE = 0.2;
						posYE = 0.73;
						posZE = 0.0;
						rotation = 90;	
						posXOld = posX;
						posYOld = posY;
						rotationOld = rotation;
}