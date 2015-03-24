//Create board
#include <iostream>
#include <vector>
#include "terrain.h"
#include "grass.h"
#include "water.h"
#include "map.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
using namespace std;

int main(){
	Map m1; //default map (all grass)
	Map m2("map2.txt"); //non-default map
	cout<<"Map 1: Default"<<endl;
	m1.display();
	cout<<"Map 2: file input"<<endl;
	m2.display();
	cout<<"Add characters to map 2"<<endl;
	m2.addCharacter(new Player(24,24,100,100,100)); //add character at (24,24)
	m2.addCharacter(new Enemy(35,35,100,100,100)); //add character at (35,35)
	m2.display();
	cout<<"~ = water, . = grass, X = character"<<endl;
}
