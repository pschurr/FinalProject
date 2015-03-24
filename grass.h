//grass.h - implementation for grass tile on board
#ifndef GRASS_H
#define GRASS_H
#include <iostream>
#include "terrain.h"
using namespace std;

class Grass: public Terrain{
	public:
		Grass();
		virtual void display();
	private:
		
		
};

Grass::Grass()
	:Terrain(){
	//isWalkedOn=false;
}

void Grass::display(){
	cout<<"G";
}

#endif
