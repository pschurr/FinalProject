//knight.h - type of playable character
#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include "character.h"
#include "Tile.h"
#include <string>
using namespace std;

class Knight:public Character{
	public:
		Knight(string,int,int,bool);
//		Knight(int,int,int,int,int,int,bool);
		virtual void render();
		virtual void display();
		bool findEnemy();
	private:
		
};

// Instantiate Knight with name, coordinates, and stats
Knight::Knight(string name,int x,int y,bool team)
        :Character(name,2,x,y,100,100,100,5,team){

}

// Determine what team the Knight is on
void Knight::render(){
myTile.renderKnight(isEnemy);
}

// Make a general display for each knight to direct gameplay
void Knight::display(){
	cout<<"Selected character: "<<mName<<endl;
	cout<<"Class: Knight"<<endl;
	cout<<"Health: "<<health<<"/"<<maxHealth<<endl;
}

#endif
