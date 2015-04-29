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
                virtual void render(bool);
		virtual void display();
        private:

};

Archer::Archer(string name,int x,int y,bool team)
        :Character(name,1,x,y,100,80,80,20,team){

}



void Archer::render(bool isEne){
        myTile.renderArcher(isEne);
}

void Archer::display(){
        cout<<"Selected character: "<<mName<<endl;
        cout<<"Class: Archer"<<endl;
        cout<<"Health: "<<health<<"/"<<maxHealth<<endl;

}

#endif

