//mage.h
#ifndef MAGE_H
#define MAGE_H
#include <iostream>
#include "character.h"
#include "Tile.h"

using namespace std;

class Mage:public Character{
        public:
                Mage(int,int,bool);
                Mage(int,int,int,int,int,int,bool);
                virtual void render();
		void heal(Character*);
        private:

};

Mage::Mage(int x,int y,bool team)
        :Character(x,y,100,80,80,5,team){

}

Mage::Mage(int x,int y,int h,int atk,int def,int r,bool team)
        :Character(x,y,h,atk,def,r,team){

}

void Mage::render(){
	//cout<<"Mage"<<endl;
        //myTile.render();
}

void Mage::heal(Character* other){
	if(other==this)
		incrHealth(15);
}

#endif

