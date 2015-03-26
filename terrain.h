//terrain.h - abstract default terrain class
#ifndef TERRAIN_H
#define TERRAIN_H
#include <iostream>
using namespace std;

class Terrain{
	public:
		Terrain();
		virtual void display() = 0;
		bool hasCharacter();
		void walkOn();
		void walkOff();
	protected:
		bool isWalkedOn;
};

Terrain::Terrain(){
	isWalkedOn=false;
}

bool Terrain::hasCharacter(){
	if(isWalkedOn)
		return true;
	else
		return false;
}

void Terrain::walkOn(){
	isWalkedOn=true;
}

void Terrain::walkOff(){
	isWalkedOn=false;
}

#endif
