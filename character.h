//character.h - abstract default character class
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <vector>
using namespace std;

class Character{
	friend class Map;
	public:
		Character();
		Character(int,int,int,int,int,int,bool);
		virtual void display()=0;
		int getX();
		int getY();
		int getHealth();
		int getAttackPwr();
		int getDefensePwr();
		int getRange();
		void moveUp(int);
		void moveDown(int);
		void moveLeft(int);
		void moveRight(int);
		void incrHealth(int);
		void decrHealth(int);
		void attack(Character *);
	protected:
		int xloc;
		int yloc;
		int health;
		int attackPwr;
		int defensePwr;
		int range; //distance from which character can attack
		bool isEnemy; //true if character is enemy, false if in player's party
		bool isAlive; //becomes false when health>=0
		vector<Character*> charsInRange; //all other characters that can be attacked
		
};

Character::Character(){
	health=100;
	attackPwr=100;
	defensePwr=100;
	range=5;
	isAlive=true;
}

Character::Character(int x,int y,int h,int atk,int def,int r,bool team){
	xloc=x;
	yloc=y;
	health=h;
	attackPwr=atk;
	defensePwr=def;
	range=r;
	isEnemy=team;
}

int Character::getX(){return xloc;}
int Character::getY(){return yloc;}
int Character::getHealth(){return health;}
int Character::getAttackPwr(){return attackPwr;}
int Character::getDefensePwr(){return defensePwr;}
int Character::getRange(){return range;}

void Character::moveUp(int dist){
	yloc-=dist;
}

void Character::moveDown(int dist){
	yloc+=dist;
}

void Character::moveLeft(int dist){
	xloc-=dist;;
}

void Character::moveRight(int dist){
	xloc+=dist;
}

void Character::incrHealth(int amt){
	health+=amt;
}

void Character::decrHealth(int amt){
	health-=amt;
	if(health<=0){
		health=0;
		isAlive=false;
		cout<<"Character defeated"<<endl;
	}
}

void Character::attack(Character * other){
	bool inRange=false;
	for(int i=0;i<charsInRange.size();i++){
		if(other==charsInRange[i]){
			inRange=true;
			break;
		}
	}
	if(!inRange){
		cout<<"Cannot attack: out of range"<<endl;
		return;
	}else{
		int damage=(int)((1.5*attackPwr-other->getDefensePwr())/2.5);
		other->decrHealth(damage);
	}
}

#endif
