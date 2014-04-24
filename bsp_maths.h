#ifndef BSP_MATHS_H_
#define BSP_MATHS_H_

typedef struct point {
	int X;
	int Y;
} Point;

typedef struct vector {
	float X;
	float Y;
} Vector;

int contains(int x, int y, int recTopX, int recTopY, int recBotX, int recBotY); //checks if point (x,y) is inside axis-aligned rectangle. returns 1 for true, 0 for false.
Point midpointRect(int x1, int y1, int x2, int y2); //returns Point structure representing the midpoint of axis-aligned rectangle.
Vector normalise(Vector v); //returns normalised vector.

#endif