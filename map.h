//map.h - Map or area that contains Terrain objects
#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "terrain.h"
using namespace std;

class Map{
	public:
		Map();
		Map(string); //Read Map elements from file
		void display(); //Display map
	private:
		vector<vector<Terrain *> > map;
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
			
		}
		map.push_back(tempVec);
		tempVec.clear();
	}
}

void Map::display(){
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			map[i][j]->display();
		}
		cout<<endl;
	}
}

#endif
