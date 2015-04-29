//mage.h
#ifndef MAGE_H
#define MAGE_H
#include <iostream>
#include "character.h"
#include "Tile.h"
#include <string>

using namespace std;

class Mage:public Character{
        public:
                Mage(string,int,int,bool);
                virtual void render();
		virtual void display();
		void heal(Character*);
        private:

};

Mage::Mage(string name,int x,int y,bool team)
        :Character(name,1,x,y,100,80,80,5,team){

}



void Mage::render(){
        myTile.render();
}

void Mage::display(){
        cout<<"Selected character: "<<mName<<endl;
        cout<<"Class: Mage"<<endl;
        cout<<"Health: "<<health<<"/"<<maxHealth<<endl;

}

void Mage::heal(Character* other){
	if(other==this)
		incrHealth(15);
}

#endif

