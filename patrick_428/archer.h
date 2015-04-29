//archer.h
#ifndef ARCHER_H
#define ARCHER_H
#include <iostream>
#include "character.h"
#include "Tile.h"
#include <string>

using namespace std;

class Archer:public Character{
        public:
                Archer(string,int,int,bool);
                virtual void render();
		virtual void display();
        private:

};

// Instantiate and archer with name, coordinates, and stats
Archer::Archer(string name,int x,int y,bool team)
        :Character(name,1,x,y,100,80,80,20,team){

}


// Determine which archer sprite to display depending what team the archer is on
void Archer::render(){
        myTile.renderArcher(isEnemy);
}

// General information displayed to help with gameflow
void Archer::display(){
        cout<<"Selected character: "<<mName<<endl;
        cout<<"Class: Archer"<<endl;
        cout<<"Health: "<<health<<"/"<<maxHealth<<endl;

}

#endif

