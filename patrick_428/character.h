//character.h - abstract default character class
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <vector>
#include "Tile.h"
#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Character{
	friend class Map;
	public:
		Character();
		Character(string,int,int,int,int,int,int,int,bool);
		virtual void render();
		virtual void display();
		int handleEvent(SDL_Event);
		int getX();
		int getY();
		int getHealth();
		int getMaxHealth();
		int getAttackPwr();
		int getDefensePwr();
		int getRange();
		void setOnMe(bool);
		void setCanMove(bool,bool,bool,bool);
		void moveUp(int);
		void moveDown(int);
		void moveLeft(int);
		void moveRight(int);
		void incrHealth(int);
		void decrHealth(int);
		void attack(Character *);
	protected:
		Tile myTile;
		int xloc;
		int myType;
		int yloc;
		int health;
		int maxHealth;
		int attackPwr;
		int defensePwr;
		int range; //distance from which character can attack
		bool isEnemy; //true if character is enemy, false if in player's party
		bool isAlive; //becomes false when health>=0
		vector<Character*> charsInRange; //all other characters that can be attacked
		string mName;		
		bool onMe;
		bool canMove[4];
};

Character::Character(){
	xloc = 0;
	yloc = 0;
	myType=0;
	maxHealth=100;
	health=maxHealth;
	attackPwr=100;
	defensePwr=100;
	range=5;
	isAlive=true;
	myTile.set_xpos(0);
	myTile.set_ypos(0);
	myTile.set_type(4);
	mName = "default";
	onMe = false;
	canMove[0]=true;
	canMove[1]=true;
	canMove[2]=true;
	canMove[3]=true;
}

Character::Character(string name,int myType,int x,int y,int h,int atk,int def,int r,bool team){
	onMe=false;
	mName = name;
	xloc=x;
	yloc=y;
	maxHealth=h;
	health=maxHealth;
	attackPwr=atk;
	defensePwr=def;
	range=r;
	isEnemy=team;
	myTile.set_xpos(xloc);
	myTile.set_ypos(yloc);
	myTile.set_type(myType);
        canMove[0]=true;
        canMove[1]=true;
        canMove[2]=true;
        canMove[3]=true;
}

int Character::getX(){return xloc;}
int Character::getY(){return yloc;}
int Character::getHealth(){return health;}
int Character::getMaxHealth(){return maxHealth;}
int Character::getAttackPwr(){return attackPwr;}
int Character::getDefensePwr(){return defensePwr;}
int Character::getRange(){return range;}

void Character::setOnMe(bool isOnMe){
	onMe=isOnMe;
}

void Character::setCanMove(bool up,bool down,bool left,bool right){
	canMove[0]=up;
	canMove[1]=down;
	canMove[2]=left;
	canMove[3]=right;
}

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
void Character::render(){
}

void Character::display(){}

int Character::handleEvent(SDL_Event e){
	int status=0;
	if(e.type==SDL_MOUSEBUTTONDOWN){
		int mousex,mousey;
	SDL_GetMouseState(&mousex,&mousey);

		if((mousex>xloc)&&(mousex<xloc+32)&&(mousey>yloc)&&(mousey<yloc+32)){
			display();
			onMe=true;
			}
		else{
			onMe=false;
			}
	}	


	if(e.type==SDL_KEYDOWN){
		if(onMe==true){
			bool moved=false;
			cout<<"Can move: "<<canMove[0]<<canMove[1]<<canMove[2]<<canMove[3]<<endl;
			switch(e.key.keysym.sym){
				case SDLK_DOWN:
					if(canMove[1]){
						yloc+=32;
						moved=true;
						break;
					}
				case SDLK_UP:
					if(canMove[0]){
						yloc-=32;
						moved=true;
						break;
					}
				case SDLK_LEFT:
					if(canMove[2]){
                                        	xloc-=32;
						moved=true;
                                        	break;
					}
				case SDLK_RIGHT:
					if(canMove[3]){
                                        	xloc+=32;
						moved=true;
                                        	break;
					}

				}
			if(moved)
				status=1;
		}
	
	}	
	myTile.set_xpos(xloc);
	myTile.set_ypos(yloc);
	return status;
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
