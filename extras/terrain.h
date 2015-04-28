//terrain.h - abstract default terrain class
#ifndef TERRAIN_H
#define TERRAIN_H
#include <iostream>
#include "character.h"
using namespace std;

class Terrain{
	public:
		Terrain();
		virtual void display() = 0;
		bool hasCharacter();
		Character* getCharacter();
		void walkOn(Character*);
		void walkOff();
	protected:
		bool isWalkedOn;
		Character * charOnSpace;
};

Terrain::Terrain(){
	isWalkedOn=false;
	charOnSpace=NULL;
}

bool Terrain::hasCharacter(){
	if(isWalkedOn)
		return true;
	else
		return false;
}

Character* Terrain::getCharacter(){return charOnSpace;}

void Terrain::walkOn(Character * newChar){
	isWalkedOn=true;
	charOnSpace=newChar;
}

void Terrain::walkOff(){
	isWalkedOn=false;
	charOnSpace=NULL;
}

#endif
