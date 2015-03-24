//water.h - implementation for water tile on board
#ifndef WATER_H
#define WATER_H
#include <iostream>
#include "terrain.h"
using namespace std;

class Water: public Terrain{
	public:
		Water();
		virtual void display();
};

Water::Water(){
	isWalkedOn=false;
}

void Water::display(){
	cout<<"w";
}

#endif
