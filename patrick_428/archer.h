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
        private:

};

Archer::Archer(string name,int x,int y,bool team)
        :Character(name,x,y,100,80,80,20,team){

}



void Archer::render(){
        myTile.render();
}

#endif

