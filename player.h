//player.h - implementation for playable character
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "character.h"
#include "enemy.h"
using namespace std;

class Player:public Character{
	public:
		Player();
		Player(int,int,int,int,int,int);
		virtual void display();
		bool findEnemy();
	private:

};

Player::Player()
	:Character(){}

Player::Player(int x,int y,int h,int atk,int def,int r)
	:Character(x,y,h,atk,def,r){
}

void Player::display(){
	cout<<"P";
}

bool Player::findEnemy(){
	for(int i=xloc-range;i<xloc+range;i++){
		for(int j=yloc-range;j<yloc+range;j++){
			
		}
	}
}

#endif
