#ifndef LEVEL_GEN_H_
#define LEVEL_GEN_H_

#include "bsp_maths.h"

#define ROOM_OFS 4

typedef struct node { //BSP tree node
	int topX;
	int topY;
	int botX;
	int botY;

	struct node * childA;
	struct node * childB;
} Node;

typedef struct room {
	int topX;
	int topY;
	int botX;
	int botY;
} Room;

void generateTree(int interations, Node * root); //Generates a BSP tree with each node having physical dimensions.
void addRooms(int ** levelArray, Room ** roomArray, int roomArrIndex, Node * root); //Recurses to leaf nodes of BSP, adds rooms to level array.
void insertPath(int ** levelArray, Point start, Point finish); //Adds a single path between two points to level array.
void addPaths(int ** levelArray, Node * root); //Recurses to leaf nodes of BSP, adds paths between each pair of nodes in tree.

#endif