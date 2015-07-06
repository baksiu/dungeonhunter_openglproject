#ifndef __GL_H
#define __GL_H

#include <iostream>
#include <list>
#include <math.h>

using namespace std;


// Klasa obslugujaca kolizje gracza z obiektami.
class CCollision {
public:
	float x, y; // polozenie srodka na plaszczyznie XY
	float m[16]; // polozenie srodka obiektu
	float r; // srednica sfery kolizyjnej
	float i; //id przeciwnika
};

// Klasa obslugujaca strzelanie
class CMissle {
public:
	float x, y, z; // polozenie pocisku
	float dir; // kierunek ruchu
};
// Klasa obslugujaca przeciwników
class CEnemy {
public:
	float x, y; // polozenie przeciwnika
	float xOld, yOld; // poprzednie po³o¿enie przeciwnika
	float dir; // kierunek ruchu
	float xe, ye;// œledzenie przeciwnika
	int id; // id przeciwnika
	int life; // ¿ycie przeciwnika
	float time; // czasdo kolejnego strza³u

};

/** Glowna klasa odpowiedzialna za sterowanie aplikacja i rysowanie grafiki. Klasa jest 'wrapperem' dla funkcji wywolywanych 
bezposrednio przez API OpenGL'a. Jej zastosowanie ma na celu wykorzystanie mechanizmow obiektowych do programowania OpenGL'a
(natywnie API OpenGL'a wymaga programowania w ANSI C)). W klasie znajduje sie szereg funkcji wywolywanych przez maszyne 
stanu OpenGL'a. Przykladem moze byc funkcja display() wywolywana w momencie, gdy wymagane jest przerysowanie ekranu.
*/

struct vec3 {
	float x, y, z;
};

class CGL {

public: 
	bool fullscreen; // fullscreen
	bool pause; // pauza
	bool game; // tryb gry
	int idx1;
	bool bb1;
	float dt_Old;

	list<int> state_list; // lista stanow
	bool keyStates[256]; // bufor klawiatury
	float t, dt, dtOld, t_old; // czas
	float t_wait, t_wait_time;
	float t_waite, t_waite_time;
	float t_waitk;
	int wait;

	float rotation,rotationY; // obrot obiektu
	float posX, posY, posZ; 
	float rotationE;
	float posXE, posYE, posZE; // translacja obiektu
	double xe,ye,ye2,xe2;
	float gravity, jump;
	float rotationOld; // poprzednia wartosc obrotu obiektu
	float posXOld, posYOld, posZOld; // poprzednie polozenie obiektu
	float posXW, posYW, posZW;
	float rotationW,rotationWOld;
	float posXWOld, posYWOld, posZWOld;
	float expX, expY;
	float obrot,wysokosc;
	float widthMagic;
	void drawWeapon();
	float grow;
	bool isJump;
	string str,str2,str3,str4,str5;
	bool komunikat1;
	GLuint tekstura,tekstura_2,tekstura_3,tekstura_4,tekstura_5,tekstura_6,tekstura_7,tekstura_8,tekstura_9;



	unsigned char* mscene; // wskaznik na dane bitmapy z informacjami o strukturze sceny
	short mscene_width;
	short mscene_height;
	int mscene_line_length;

	list<CCollision> collision_list;
	list<CCollision> collision_list2;
	list<CCollision> collision_list3;
	list<CCollision> collision_list4; // lista z obietkami, dla ktorych liczone sa kolizje
	CCollision collisionTarget; 
	CCollision collisionTargetBullet;
	bool isCollision;

	int pmaterial; // indeks materialu czajnika (zmieniany po kolizji)
	int id;

	list<CMissle*> missle_list; // lista z definicjami pociskow
	list<CMissle*> missle_list_enemy; // lista z definicjami pociskow przeciwnika
	list<CEnemy*> enemy_list; // lista z definicjami przeciwników
	list<CEnemy*>::iterator ie; // literator przeciwników
	list<CMissle*>::iterator ite; // literator pocisków przeciwników

public:

	CGL() {
		
		state_list.clear(); // kasowanie listy stanow

		for(int i=0;i<256;i++) // kasowanie bufora klawiatury
			keyStates[i] = 0;

		//isCollision = false;
		pmaterial = MATERIAL_PLAYER_RED;
		missle_list.clear();
	}
	/////przeciwnicy
	void drawEnemy ( CEnemy* ce ); //rysowanie przeciwnika
	void enemyShoot (void); //strza³y przeciwnika
	/////menu i hud
	void drawMenu (void); // rusuje menu
	void Play (int button, int state, int x, int y); // uruchamia grê
	void NewGame  (void); //nowa gra
	void EndGame (void); // koniec gry
	void GameOver (void); // wyœwietla plansze o koñcu gry
	void Pause (void); // pauza
	void Fullscreen (void); // fullscreen
	void Exit (void); // wy³¹cza grê
	void Life ( void); // pasek zdrowia
	/////gracz i scena
	void init( void ); // Inicjalizacja srodowiska graficznego
	void display( void ); // przerysowanie sceny
	void drawObject( void ); 
	void drawEnemy( void );// rysowanie przeciwnika
	void keyPress( unsigned char key,int a,int b ); // nacisniecie klawiatury
	void keyUp( unsigned char key,int a,int b ); // puszczenie klawisza klawiatury
	void myszka( int button, int state, int x, int y); // myszka??
	void myszkaRuch(int x, int y); // ruch myszki??
	void keyOperations( void ); // obsluga klawiatury
	void drawScene( void ); // rysowanie sceny
	void drawMissle( CMissle* cm ); // rysowanie pociskow
	void drawMissle2( CMissle* cm );
	void drawMagic(int id); 
	void newMap(void);
	GLuint loadBMPtexture(const char* filename);
	void CGL::multipleEnemies(int scale);
	void CGL::drawExplosion(void);
	void CGL::highscoresave(int score,int kill);
	bool CGL::highscoreload();
	void wyswietlWyniki(int a, int b);
	void CGL::wyswietlWynikiOrtho(int a,int b, int i);
	string CGL::intTostr(int score);
	string CGL::intTostr(float time);
	string komunikat;

	//////////magia
	int CGL::icesicle(int magic);
	int CGL::fireball(int magic);



	/** Pomocnicza funkcja sprawdzajaca czy na liscie stanow wystepuje dany stan
	 */
	bool findState( int state ) {
		
		list<int> states = state_list;
		list<int>::iterator state_it;
		
		for( state_it = states.begin(); state_it != states.end(); ++state_it) {
			
			if ( *state_it == state ) {
				return true;
			}
		}
		return false;
	}
	
	// Funkcja z definicjami materialow
	void setMaterial( int id ) {

		switch( id ) {

			case MATERIAL_PLAYER_RED:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorRed );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorDim );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorGray );
				glMateriali( GL_FRONT, GL_SHININESS, 20 );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorRed );
				break;

			case MATERIAL_PLAYER_BLUE:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorBlue );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorDim );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorDim );
				//glMaterialf( GL_FRONT, GL_SHININESS, 0.0f );
				//glMaterialfv( GL_FRONT, GL_EMISSION, colorDim );
				break;

			case MATERIAL_WALL_BLUE:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorBlue );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorDim );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorDim );
				glMaterialf( GL_FRONT, GL_SHININESS, 0.0f );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorBlue );
				break;

			case MATERIAL_WALL_PINK:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorPINK );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorDim );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorDim );
				glMaterialf( GL_FRONT, GL_SHININESS, 15.0f );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorPINK );
				break;
			case MATERIAL_WALL_GRAY:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorGray );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorDim );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorDim );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorDim );
				glMateriali( GL_FRONT, GL_SHININESS, 15);
				break;

			case MATERIAL_WALL_RED:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorRed );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorDim );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorDim );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorDim );
				break;

			case MATERIAL_WALL_GREEN:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorDarkGreen );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorDim );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorDim );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorDim );
				break;
			case MATERIAL_WALL_YELLOW:
				glMaterialfv( GL_FRONT, GL_DIFFUSE, colorGray );
				glMaterialfv( GL_FRONT, GL_AMBIENT, colorYellow );
				glMaterialfv( GL_FRONT, GL_SPECULAR, colorGray );
				glMaterialfv( GL_FRONT, GL_EMISSION, colorYellow );
				glMateriali( GL_FRONT, GL_SHININESS, 15);
				break;

		}

	}


	// Konwersja polozenia w bitmapie na indeks liniowy
	int xy2idx( int x, int y ) {
		return x * 3 + y * mscene_line_length;
	}

	// konwersja wspolrzednych sceny na wspolrzedne tablicy, 
	// funkcja zwraca true w przypadku wyjscia indeksu poza tablice
	bool xy2mscene( float x, float y, int &ix, int &iy ) {

		bool f = false;

		ix = (int)( mscene_width * x );
		iy = (int)( mscene_height * y );

		if( x < 0 )
			f = true;
		if( y < 0 )
			f = true;

		if( ix < 0 ) {
			ix = 0;
			f = true;
		}
		if( iy < 0 ) {
			iy = 0;
			f = true;
		}
		if( ix >= mscene_width ) {
			ix = mscene_width - 1;
			f = true;
		}
		if( iy >= mscene_height ) {
			iy = mscene_height - 1;
			f = true;
		}

		return f;
	}

	bool xy2mscene( float x, float y, int &idx ) {

		int ix, iy;
		bool f = xy2mscene( x, y, ix, iy );
		if( f == false )
			idx = xy2idx( ix, iy );
		else
			idx = 0;

		return f;
	}



	// dodanie obiektu do listy obiektow, dla ktorych sprawdzane sa kolizje
	bool addCollision( float r ) {

		CCollision col;
		glGetFloatv( GL_MODELVIEW_MATRIX, col.m );

		col.r = r;
		collision_list.push_back( col );

		//glutWireSphere( 1.5, 10, 10 );
		
		return true;
	}
	bool addCollisionDetection( float r ) {

		CCollision colDetection;
		glGetFloatv( GL_MODELVIEW_MATRIX, colDetection.m );

		colDetection.r = r;
		collision_list4.push_back( colDetection );

		//glutWireSphere( 1.5, 10, 10 );
		
		return true;
	}
	bool addCollisionEnemy( float r ) {

		CCollision colEnemy;
		glGetFloatv( GL_MODELVIEW_MATRIX, colEnemy.m );

		colEnemy.r = r;
		collision_list2.push_back( colEnemy );

		//glutWireSphere( 1.5, 10, 10 );
		
		return true;
	}
	bool addCollisionBullet( float r ) {

		CCollision colBullet;
		glGetFloatv( GL_MODELVIEW_MATRIX, colBullet.m );

		colBullet.r = r;
		collision_list3.push_back( colBullet );

		//glutWireSphere( 1.5, 10, 10 );
		
		return true;
	}
	// detekcja kolizji dla danego obiektu
	bool detectCollision( CCollision colTarget ) {

		list<CCollision> collisions = collision_list;
		list<CCollision>::iterator iter;
		for( iter = collision_list.begin(); iter != collision_list.end(); ++iter) {

			CCollision col = *iter; 

			float len = sqrt( (colTarget.m[12+0]-col.m[12+0])*(colTarget.m[12+0]-col.m[12+0]) + (colTarget.m[12+1]-col.m[12+1])*(colTarget.m[12+1]-col.m[12+1])
				+ (colTarget.m[12+2]-col.m[12+2])*(colTarget.m[12+2]-col.m[12+2]) );

			if( len < ( colTarget.r + col.r ) )
				return true;
		}

		return false;
	}
	bool detectCollisionEnemy( CCollision colTarget ) {

		list<CCollision> collisions = collision_list2;
		list<CCollision>::iterator iter;
		for( iter = collision_list2.begin(); iter != collision_list2.end(); ++iter) {

			CCollision col = *iter; 

			float len = sqrt( (colTarget.m[12+0]-col.m[12+0])*(colTarget.m[12+0]-col.m[12+0]) + (colTarget.m[12+1]-col.m[12+1])*(colTarget.m[12+1]-col.m[12+1])
				+ (colTarget.m[12+2]-col.m[12+2])*(colTarget.m[12+2]-col.m[12+2]) );

			if( len < ( colTarget.r + col.r ) )
				return true;
		}

		return false;
	}
	bool detectCollisionBullet( CCollision colTarget ) {

		list<CCollision> collisions = collision_list3;
		list<CCollision>::iterator iter;
		for( iter = collision_list3.begin(); iter != collision_list3.end(); ++iter) {

			CCollision col = *iter; 

			float len = sqrt( (colTarget.m[12+0]-col.m[12+0])*(colTarget.m[12+0]-col.m[12+0]) + (colTarget.m[12+1]-col.m[12+1])*(colTarget.m[12+1]-col.m[12+1])
				+ (colTarget.m[12+2]-col.m[12+2])*(colTarget.m[12+2]-col.m[12+2]) );

			if( len < ( colTarget.r + col.r ) )
				return true;
		}

		return false;
	}
	bool detectCollisionDetection( CCollision colTarget ) {

		list<CCollision> collisions = collision_list4;
		list<CCollision>::iterator iter;
		for( iter = collision_list4.begin(); iter != collision_list4.end(); ++iter) {

			CCollision col = *iter; 

			float len = sqrt( (colTarget.m[12+0]-col.m[12+0])*(colTarget.m[12+0]-col.m[12+0]) + (colTarget.m[12+1]-col.m[12+1])*(colTarget.m[12+1]-col.m[12+1])
				+ (colTarget.m[12+2]-col.m[12+2])*(colTarget.m[12+2]-col.m[12+2]) );

			if( len < ( colTarget.r + col.r ) )
				return true;
		}

		return false;
	}
	
	
};

extern CGL cgl;

#endif


