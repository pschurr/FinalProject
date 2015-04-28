//knight.h - type of playable character
#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include "character.h"
#include "Tile.h"

using namespace std;

class Knight:public Character{
	public:
		Knight();
		Knight(int,int,int,int,int,int,bool);
		virtual void render();
		bool findEnemy();
	private:

};

Knight::Knight()
	:Character(){

}

Knight::Knight(int x,int y,int h,int atk,int def,int r,bool team)
	:Character(x,y,h,atk,def,r,team){
	
}

void Knight::render(){
	myTile.render();
}

#endif
