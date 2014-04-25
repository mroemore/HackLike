#include <stdio.h>
#include <stdlib.h>

#include "bsp_maths.h"
#include "level_gen.h"

void generateTree(int iterations, Node * root){
	if(iterations > 0){
		iterations--;

		root->childA = malloc(sizeof(Node));
		root->childB = malloc(sizeof(Node));
		
		int offset = (ROOM_OFS/2) - rand() % ROOM_OFS; //Offset defines the variance in the splitting of the current BSP square. 

		int direction = rand()%100;

		if(direction > 50){ //Splitting along the X axis
			int difX = root->botX - root->topX;

			root->childA->topX = root->topX;
			root->childA->topY = root->topY;
			root->childA->botX = root->topX + (int)((difX/2) + offset);  //New X is previous X plus 1/2 the size of the square plus the offset.
			root->childA->botY = root->botY;

			root->childB->topX = root->childA->botX;
			root->childB->topY = root->topY;
			root->childB->botX = root->botX;
			root->childB->botY = root->botY;

		} else { //Splitting along the Y axis
			int difY = root->botY - root->topY;

			root->childA->topX = root->topX;
			root->childA->topY = root->topY + (int)((difY/2) + offset);
			root->childA->botX = root->botX;
			root->childA->botY = root->botY;

			root->childB->topX = root->topX;
			root->childB->topY = root->topY;
			root->childB->botX = root->botX;
			root->childB->botY = root->childA->topY;
		}

		generateTree(iterations, root->childA); //Recursion! Do it again, but better.
		generateTree(iterations, root->childB);
	}
}

void addRooms(int ** levelArray, Room ** roomArray, int roomArrIndex, Node * root){
	printf("x ");
	if(root->childA == NULL) {
		int difX = root->botX - root->topX;
		int difY = root->botY - root->topY;

		if(difY <= 3){ //Might fix divide by zero error.. it did. Probably needs a better fix.
			difY = 3;
		}
		if(difX <= 3){
			difX = 3;
		}

		int topXoff = (int)(rand() % (difX/3)); //Room offset is at most 1/3 (on each axis) the length of the node.
		int topYoff = (int)(rand() % (difY/3)); //Offset meaning the space between the BSP square size and the actual room size.
		int botXoff = (int)(rand() % (difX/3));
		int botYoff = (int)(rand() % (difY/3));

		roomArray[roomArrIndex]->topX = root->topX + topXoff;
		roomArray[roomArrIndex]->topY = root->topY + topYoff;
		roomArray[roomArrIndex]->botX = root->botX + botXoff;
		roomArray[roomArrIndex]->botY = root->botY + botYoff;

		roomArrIndex++;

		for(int i = root->topX+1 + topXoff; i < root->botX-1 - botXoff; i++){
			for(int j = root->topY+1 + topYoff; j < root->botY-1 - botYoff; j++){
				levelArray[i][j] = 1;
			}
		}
	} else {
		addRooms(levelArray, roomArray, roomArrIndex, root->childA); //More recursion! Aw yeah.
		addRooms(levelArray, roomArray, roomArrIndex, root->childB);
	}
}



void insertPath(int ** levelArray, Point start, Point finish){
	int lowerX  = 0;
	int lowerY  = 0;
	int higherX = 0;
	int higherY = 0;

	if(start.X >= finish.X){ //finds which of start or finish has the higher X value
		lowerX = finish.X;
		higherX = start.X;
	} else {
		lowerX = start.X;
		higherX = finish.X;
	}

	if(start.Y >= finish.Y){ //finds which of start or finish has the higher Y value
		lowerY = finish.Y;
		higherY = start.Y;
	} else {
		lowerY = start.Y;
		higherY = finish.Y;
	}

	int midpoint = lowerX + (higherX - lowerX)/2;
	int y = lowerY;

	for(int i = lowerX; i < higherX; i++){

		if(i > midpoint){
			y = higherY;
		}

		if(levelArray[i][y] == 0){
			levelArray[i][y] = 2;
		}
	}

	for(int i = lowerY; i < higherY; i++){
		if(levelArray[midpoint][i] == 0){
			levelArray[midpoint][i] = 2;
		}
		
	}
}

void addPaths(int ** levelArray, Node * root){
	if(root->childA != NULL){
		Point start, finish;
		start  = midpointRect(root->childA->topX, root->childA->topY, root->childA->botX, root->childA->botY);
		finish = midpointRect(root->childB->topX, root->childB->topY, root->childB->botX, root->childB->botY);

		insertPath(levelArray, start, finish);

		addPaths(levelArray, root->childA);
		addPaths(levelArray, root->childB);
	}
}