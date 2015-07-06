#ifndef PLAYER_H
#define PLAYER_H

class playerstats {

public:
	int health, stamina, exp;
	int lvlstat,killedstat;
	void addHealth(int liczba);
	playerstats(){
		health=stamina=50;
		exp=0;
		lvlstat=0;
		killedstat=0;
	};
	~playerstats(){
		health=stamina=exp=0;
	};
};
class playerequipment {
public:
	int idMagic, qntEstus,qntMagic1,qntMagic2;
	bool shortsword, bow, greatsword;
	playerequipment(){
		idMagic = 0;
		qntMagic1 = 0;
		qntMagic2 = 0;
		qntEstus = 3;
		shortsword = true;
		bow = greatsword = false;
	};
	~playerequipment(){
		idMagic = 0;
		qntEstus = 0;
		shortsword = bow = greatsword = false;
	};
};
class magicstats{



};
class weaponstats{

};
class enemystats {

public:
	int health;

	void addDamage(int liczba);
	enemystats(){
		health=10;
	};
	~enemystats(){
		health=0;
	};
};
class weapon {
public:
	float posXW, posYW, posZW;
	float rotationW;
	void drawWeapon();
};

#endif