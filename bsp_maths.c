#include <math.h>

#include "bsp_maths.h"

int contains(int x, int y, int recTopX, int recTopY, int recBotX, int recBotY){
	if(x >= recTopX && x <= recBotX && y >= recTopY && y <= recBotY){
		return 1;
	} else {
		return 0;
	}
}

Point midpointRect(int x1, int y1, int x2, int y2){
	Point point;

	point.X = x1 + (x2 - x1)/2;
	point.Y = y1 + (y2 - y1)/2;

	return point;
}

Vector normalise(Vector v){
	float length = sqrt((v.X * v.X) + (v.Y + v.Y));
	Vector normalised;
	
	normalised.X = v.X/length;
	normalised.Y = v.Y/length;

	return normalised;
}