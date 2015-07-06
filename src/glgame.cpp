
#include "conf.h"
#include "glut.h"
#include "gl.h"
#include "player.h"

// obsluga klawiatury

void keyUp( unsigned char key,int a,int b ) {
	cgl.keyUp( key, a, b );	
}

void keyPress( unsigned char key, int a, int b ) {
	cgl.keyPress( key, a, b );
}

void myszka(int button, int state, int x, int y)
{
	cgl.myszka(button,state,x,y);
}
void myszkaRuch(int x, int y)
{
	cgl.myszkaRuch(x,y);
}
// przerysowanie ekranu
void display(void) {
	cgl.display();
}


//
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize( 880, 800 );
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Dungeon Hunter");
    glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(myszka);
	glutMotionFunc(myszkaRuch);
	glutPassiveMotionFunc(myszkaRuch);


	 
	cgl.init();
    glutMainLoop();
}


