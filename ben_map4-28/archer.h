//archer.h
#ifndef ARCHER_H
#define ARCHER_H
#include <iostream>
#include "character.h"
#include "Tile.h"

using namespace std;

class Archer:public Character{
        public:
                Archer(int,int,bool);
                Archer(int,int,int,int,int,int,bool);
                virtual void render();
        private:

};

Archer::Archer(int x,int y,bool team)
        :Character(x,y,100,80,80,20,team){

}

Archer::Archer(int x,int y,int h,int atk,int def,int r,bool team)
        :Character(x,y,h,atk,def,r,team){

}

void Archer::render(){
	cout<<"Archer"<<endl;
        //myTile.render();
}

#endif

