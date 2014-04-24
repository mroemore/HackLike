#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "bsp_maths.h"
#include "level_gen.h"

#define MAP_W 80
#define MAP_H 80
//span of room offset. if 6, it will be + or - 3.

void drawLevel(int ** levelArray);

int main(int argc, char ** argv){
	srand(time(NULL));
	int treeDepth = 4; //pretty important variable. determines BSP tree depth and therefore dungeon size.

	if(argc > 1){
		treeDepth = argv[1][0] - '0'; //char to int conversion of argument.
	}

	int roomCount = pow(2, treeDepth);

	Room ** roomArray;
	roomArray = (Room **) malloc(sizeof(Room) * roomCount);
	roomArray[0] = malloc(sizeof(Room));
	roomArray[0]->topX = 10;
	printf("%d", roomArray[0]->topX);

	Node * node; //root node of BSP tree
	node = malloc(sizeof(Node));
	node->topX = 0;
	node->topY = 0;
	node->botX = MAP_W;
	node->botY = MAP_H;

	//declaring and initialising level array.
	int ** level;
	level = (int **) malloc(MAP_W * sizeof(int *));

	for(int i = 0; i < MAP_W; i++){
		level[i] = (int *) malloc(MAP_H * sizeof(int));
		for(int j = 0; j < MAP_H; j++){
			level[i][j] = 0;
		}
	}

	//Level generation functions
	generateTree(treeDepth, node);
	addRooms(level, roomArray, node);
	addPaths(level, node);

	drawLevel(level);

	return 0;
}

void drawLevel(int ** levelArray){
	for(int i = 0; i < MAP_W; i++){
		for(int j = 0; j < MAP_H; j++){
			switch(levelArray[i][j]) {
				case 0:
					printf(". ");
					break;
				case 1:
					printf("__");
					break;
				case 2:
					printf("zz");
					break;
			}

		}
		printf("\n");
	}
}