#include "SDL2/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "bsp_maths.h"
#include "level_gen.h"

const int MAP_W = 80;
const int MAP_H = 80;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//span of room offset. if 6, it will be + or - 3.

void drawLevel(int ** levelArray); //draws level array to console.

int main(int argc, char * args[]){
	srand(time(NULL));
	int treeDepth = 4; //pretty important variable. determines BSP tree depth and therefore dungeon size.

	//////////////////////
	// SDL STUFF BEGINS //
	//////////////////////

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	//Initialize SDL
    if(SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("HackLike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
        	printf( "Window could not be created! Boo-hoo! SDL_Error: %s\n", SDL_GetError() );
        } else {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            
            //Update the surface
            SDL_UpdateWindowSurface(window);

            //Wait two seconds
            SDL_Delay(2000);
        }
    }

    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    ////////////////////
	// SDL STUFF ENDS //
	////////////////////

	if(argc > 1){
		treeDepth = args[1][0] - '0'; //char to int conversion of argument.
	}

	int roomCount = pow(2, treeDepth);

	Room ** roomArray;
	roomArray = (Room **) malloc(sizeof(Room) * roomCount);
	for(int i = 0; i < roomCount; i++){
		roomArray[i] = malloc(sizeof(Room));
	}
	

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
	//generateTree(treeDepth, node);
	//addRooms(level, roomArray, 0, node);
	//addPaths(level, node);

	//drawLevel(level);

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
