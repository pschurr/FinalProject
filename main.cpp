//Create board
#include <iostream>
#include <vector>
#include "terrain.h"
#include "grass.h"
#include "water.h"
#include "map.h"
#include "character.h"
//#include "player.h"
//#include "enemy.h"
#include "knight.h"
using namespace std;

int main(){
	Map m1; //default map (all grass)
	Map m2("map2.txt"); //non-default map
	cout<<"Map 1: Default"<<endl;
	m1.display();
	cout<<"Map 2: file input"<<endl;
	m2.display();
	cout<<"Add characters to map 2"<<endl;
	
	Character* c1=new Knight(13,26,100,100,100,5,false);
	Character* c2=new Knight(13,29,100,100,100,5,true);
	m2.addCharacter(c1);
	m2.addCharacter(c2);
	//m2.addCharacter(new Knight(35,32,100,100,100,5)); //add character at (24,24)
	//m2.addCharacter(new Knight(35,35,100,100,100,5)); //add character at (35,35)
	m2.display();
	cout<<"~ = water, . = grass, P = player, E = enemy"<<endl;
//	m2.showCharacters();
	m2.checkCharsInRange();
	m2.showCharsInRange();
	c1->attack(c2);
	cout<<c2->getHealth()<<endl;
	c1->attack(c2);
	cout<<c2->getHealth()<<endl;
	Character* c3=new Knight(21,25,100,100,100,5,false);
	m2.addCharacter(c3);
	c3->attack(c2);
	cout<<c2->getHealth()<<endl;
	
	c1->attack(c2);
	cout<<c2->getHealth()<<endl;
	c1->attack(c2);
	cout<<c2->getHealth()<<endl;
	c1->attack(c2);
	cout<<c2->getHealth()<<endl;
}
