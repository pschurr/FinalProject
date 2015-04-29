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

// Instantiate mage with name, coordinates, and stas
Mage::Mage(string name,int x,int y,bool team)
        :Character(name,0,x,y,100,100,80,5,team){

}


// Determine which mage sprite display depending what team mage is on
void Mage::render(){
        myTile.renderMage(isEnemy);
}

// General information displayed to help gameflow
void Mage::display(){
        cout<<"Selected character: "<<mName<<endl;
        cout<<"Class: Mage"<<endl;
        cout<<"Health: "<<health<<"/"<<maxHealth<<endl;

}

// Healing ability to increase a character's health by 15 points
void Mage::heal(Character* other){
	if(other==this)
		incrHealth(15);
}

#endif

