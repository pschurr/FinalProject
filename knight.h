//knight.h - type of playable character
#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include "character.h"
using namespace std;

class Knight:public Character{
	public:
		Knight();
		Knight(int,int,int,int,int,int,bool);
		virtual void display();
		bool findEnemy();
	private:

};

Knight::Knight()
	:Character(){

}

Knight::Knight(int x,int y,int h,int atk,int def,int r,bool team)
	:Character(x,y,h,atk,def,r,team){
	
}

void Knight::display(){
	cout<<"K";
}

#endif
