//Create board
#include <iostream>
#include <vector>
#include "terrain.h"
#include "grass.h"
#include "water.h"
#include "map.h"
using namespace std;

int main(){
	/*vector<vector<Terrain *> > map;
	//Terrain *  map[10][10];
	for(int i=0;i<50;i++){
		vector<Terrain *> tempVec;
		for(int j=0;j<50;j++){
			if(i+j==25){
				tempVec.push_back(new Water());
			}else{
				tempVec.push_back(new Grass());
			}
		}
		map.push_back(tempVec);
	}
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			map[i][j]->display();
		}
		cout<<endl;
	}*/

	Map m1;
	Map m2("map2.txt");
	m1.display();
	m2.display();
}
