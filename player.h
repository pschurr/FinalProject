//player.h - implementation for playable character
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "character.h"
using namespace std;

class Player:public Character{
	public:
		Player();
		Player(int,int,int,int,int);
		virtual void display();
	private:

};

Player::Player()
	:Character(){}

Player::Player(int x,int y,int h,int atk,int def)
	:Character(x,y,h,atk,def){

}

void Player::display(){
	cout<<"P";
}

#endif
