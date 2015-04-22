//map.h - Map or area that contains Terrain objects
#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "terrain.h"
#include "character.h"
using namespace std;

class Map{
	public:
		Map();
		Map(string); //Read Map elements from file
		void addCharacter(Character *); //Add a character to map
		void display(); //Display map
		void showCharsInRange(); //Show list of characters on map
		void checkCharsInRange();
	private:
		vector<vector<Terrain *> > map;
		vector<Character *> characters; //all characters on map
};

Map::Map(){
	vector<Terrain *> tempVec;
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			tempVec.push_back(new Grass());
		}
		map.push_back(tempVec);
		tempVec.clear();
	}
	
}

Map::Map(string filename){
	ifstream infile;
	infile.open(filename.c_str());
	vector<Terrain *> tempVec;
	while(!infile.eof()){
		for(int i=0;i<50;i++){
			char c;
			infile>>c;
			if(c=='G')
				tempVec.push_back(new Grass());
			else if(c=='W')
				tempVec.push_back(new Water());
			else
				tempVec.push_back(new Grass());
		}
		map.push_back(tempVec);
		tempVec.clear();
	}
}

void Map::addCharacter(Character * newChar){
	int x=newChar->getX();
	int y=newChar->getY();
	map[x][y]->walkOn(newChar);
	characters.push_back(newChar);
}

void Map::display(){
	for(int i=0;i<25;i++){
		for(int j=0;j<50;j++){
			map[i][j]->display();
		}
		cout<<endl;
	}
}

void Map::showCharsInRange(){
	for(int i=0;i<characters.size();i++){
		for(int j=0;j<characters[i]->charsInRange.size();j++){
			if(characters[i]->charsInRange[j]!=NULL){
				cout<<"At "<<characters[i]->getX()<<", "<<characters[i]->getY()<<": ";
				cout<<"Enemy found within range!"<<endl;
			}
		}
	}
}

void Map::checkCharsInRange(){
	for(int i=0;i<characters.size();i++){
		//Character c=characters[i];
		for(int j=characters[i]->getX()-characters[i]->getRange();
			j<characters[i]->getX()+characters[i]->getRange();j++){
			for(int k=characters[i]->getY()-characters[i]->getRange();
				k<characters[i]->getY()+characters[i]->getRange();k++){
				//if(map[i][j].hasCharacter())
				if(map[j][k]->getCharacter()!=characters[i])
					characters[i]->charsInRange.push_back(map[j][k]->getCharacter());

			}
		}
	}
}

#endif
