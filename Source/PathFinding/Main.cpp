#include "Header.h"

int main(int argc, char *argv[])
{
	//Setup the window and surface
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL and check for errors
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL init failed " << SDL_GetError() << endl;
	}
	else
	{
		//Create window and check for errors
		window = SDL_CreateWindow("Pathfinding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GRID_W * CELL_W, GRID_H * CELL_H, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			cout << "Window could not be created " << SDL_GetError() << endl;
		}
		else
		{
			//Get screen surface from created window
			screenSurface = SDL_GetWindowSurface(window);
			SDL_UpdateWindowSurface(window);
		}
	}

	//Create new scene
	shared_ptr<Scene> scene = make_shared<Scene>(newColour(0, 0, 0));

	//Execute the game loop
	bool isPlaying = true;
	int lastTick = SDL_GetTicks();
	while (isPlaying){

		//Calculate delta time
		unsigned int currentTick = SDL_GetTicks();
		float deltaTime = (float) (currentTick - lastTick) / 1000.0f;
		lastTick = currentTick;

		//Update and draw scene
		scene->Draw(screenSurface);
		isPlaying = scene->Update(deltaTime);

		//Update window with surface
		SDL_UpdateWindowSurface(window);

		//Limit the fps if its running too high
		if(deltaTime < (1.0f/50.0f)) 
		{
			SDL_Delay((unsigned int) (((1.0f/50.0f) - deltaTime)*1000.0f) );
		}
	}

	//Destroy window and quit SDL
	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}