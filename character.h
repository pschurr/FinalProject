//character.h - abstract default character class
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
using namespace std;

class Character{
	public:
		Character();
		Character(int,int,int,int,int);
		virtual void display()=0;
		int getX();
		int getY();
		int getHealth();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void incrHealth(int);
		void decrHealth(int);
		
	protected:
		int xloc;
		int yloc;
		int health;
		int attackPwr;
		int defensePwr;
};

Character::Character(){
	health=100;
	attackPwr=100;
	defensePwr=100;
}

Character::Character(int x,int y,int h,int atk,int def){
	xloc=x;
	yloc=y;
	health=h;
	attackPwr=atk;
	defensePwr=def;
}

int Character::getX(){return xloc;}
int Character::getY(){return yloc;}
int Character::getHealth(){return health;}

void Character::moveUp(){
	yloc--;
}

void Character::moveDown(){
	yloc++;
}

void Character::moveLeft(){
	xloc--;
}

void Character::moveRight(){
	xloc++;
}

void Character::incrHealth(int amt){
	health+=amt;
}

void Character::decrHealth(int amt){
	health-=amt;
}


#endif
