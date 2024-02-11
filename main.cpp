#include <raylib.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#define W 10
#define SAND_COLOR {245, 161, 0, 255} 
#define GRIDPASS(S) for(int i=0;i<S;++i) for(int j=0;j<S;++j)

bool DEBUG;
typedef struct sand {
	bool active;
	Rectangle shape;
	Color color;
} sand;

Rectangle square(int i, int j, float size){
	return Rectangle{i*1.f*size, j*1.f*size, size, size};
}

int main(int argc, char **argv) {
	srand(time(NULL));
	ORANGE;
	if(argc > 1) DEBUG = (argv[1] == std::string("debug"));
	const int screen = 800;
	const int gridSize = screen / W;
	const int squareSize = screen / gridSize;
    InitWindow(screen, screen, "Grid");
	SetTargetFPS(60);
	
	double currentTime = GetTime();
	double previousTime = currentTime;
	double elapsedTime = 0.0;

	std::pair<Rectangle,Color> grid[gridSize][gridSize];
	sand sandGrid[gridSize][gridSize];

	GRIDPASS(gridSize){
		sandGrid[i][j] = sand{false, square(i, j, squareSize), SAND_COLOR};
	};
	GRIDPASS(gridSize){
		grid[i][j] = {square(i, j, squareSize), WHITE};
	};

    while (!WindowShouldClose()) {
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsCursorOnScreen()){
			Vector2 mp = GetMousePosition();
			int x = mp.x / squareSize;
			int y = mp.y / squareSize;
			if(!sandGrid[x][y].active){
				sandGrid[x][y].active = true;
				sandGrid[x][y].color = Color{(unsigned char)(20 + rand()%235+1), (unsigned char)(166+rand()%10+1), 0, 255};
			}
			if(DEBUG) std::cout << x << '-' << y << std::endl;
		}
		if(IsKeyPressed(KEY_ESCAPE)) break;
        BeginDrawing();
        ClearBackground(RAYWHITE);
		GRIDPASS(gridSize){
			DrawRectangleRec(grid[i][j].first, grid[i][j].second);
			if(sandGrid[i][j].active)DrawRectangleRec(sandGrid[i][j].shape, sandGrid[i][j].color);
		}
        EndDrawing();
		currentTime = GetTime();
		elapsedTime += currentTime - previousTime;
		previousTime = currentTime;
		if(elapsedTime >= 0.01){
			elapsedTime = 0;	
			for(int i = gridSize; i >= 0; --i){
				for(int j = gridSize; j >= 0; --j){
					int belowR, belowL;
					if(j+1 < gridSize){
						if(i-1 >= 0) belowR = 1;
					}
					if(sandGrid[i][j].active &&\
							j+1 < gridSize){
						if(!sandGrid[i][j+1].active){
							sandGrid[i][j].active = false;
							sandGrid[i][j+1].active = true;
							sandGrid[i][j+1].color = sandGrid[i][j].color;
							continue;
						}
						int dir;
						if(i-1 < 0) dir = 1;
						else if(i+1 >= screen) dir = -1;
						else dir = (rand()%2 == 0? 1:-1);
						if(!sandGrid[i+dir][j+1].active){
							sandGrid[i+dir][j+1].active = true;
							sandGrid[i+dir][j+1].color = sandGrid[i][j].color;
							sandGrid[i][j].active = false;
							continue;
						}
					}
				}
			}
		}
		
    }
    CloseWindow();

    return 0;
}

