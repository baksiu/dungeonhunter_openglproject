#include "conf.h"
#include "glut.h"
#include "gl.h"

GLuint CGL::loadBMPtexture(const char* filename)
{
	cout << "???"  <<endl;
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char *data;

	FILE *texture=fopen(filename,"rb");
	if(!texture)
	{ 
		printf("Nie mozna zaladowac tekstury %s",filename);
		return 0;
	}
	if(fread(header,1,54,texture)!=54)
	{
		printf("Nieprawidlowy format tekstury %s",filename);
		return 0;
	}
	if(header[0]!='B' || header[1]!='M')
	{
		printf("Nieprawidlowy format tekstury %s",filename);
		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	cout << dataPos <<" "<< imageSize <<" "<< width <<" "<< height <<" "<< endl;
	//uzupelnianie danych
	if(imageSize == 0)
		imageSize = width*height*3;
	if(dataPos == 0)
		dataPos=54;
	
	//czytanie danych 
	data = new unsigned char[imageSize];
	fread(data,1,imageSize,texture);
	fclose(texture);

	for (int i = 0; i < width*height; i++)
	{
		int index = i*3;
		unsigned char B, R;
		B = data[index];
		R = data[index+2];
		data[index] = R;
		data[index+2] = B;
	}
	
	// czesc mapowania
	GLuint textureID;
	glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);

	cout << textureID <<endl;
	return textureID;

}