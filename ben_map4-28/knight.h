//knight.h - type of playable character
#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include "character.h"
#include "Tile.h"

using namespace std;

class Knight:public Character{
	public:
		Knight(int,int,bool);
//		Knight(int,int,int,int,int,int,bool);
		virtual void render();
	private:
		
};


Knight::Knight(int x,int y,bool team)
        :Character(x,y,100,100,100,5,team){

}

	

void Knight::render(){
	//myTile.set_xpos(getX());
	//myTile.set_ypos(getY());
	myTile.render();
}

#endif
