//enemy.h - implementation for enemy character
#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include "character.h"
using namespace std;

class Enemy:public Character{
	public:
		Enemy();
		Enemy(int,int,int,int,int);
		virtual void display();
	private:

};

Enemy::Enemy()
	:Character(){}

Enemy::Enemy(int x,int y,int h,int atk,int def)
	:Character(x,y,h,atk,def){

}

void Enemy::display(){
	cout<<"E";
}

#endif
