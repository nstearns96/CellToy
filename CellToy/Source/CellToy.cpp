#include <SDL/SDL.h>
#undef main

void main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Rect displayBounds;
	SDL_GetDisplayBounds(0, &displayBounds);
	if (SDL_GetDisplayBounds(0, &displayBounds) != 0) {
		SDL_Log("SDL_GetDisplayBounds failed: %s", SDL_GetError());
	}

	SDL_Window* mainWindow = SDL_CreateWindow(
		"Cell Toy", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		displayBounds.w, displayBounds.h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED
	);

	SDL_Event ev;
	bool isRunning = true;
	while (isRunning)
	{
		SDL_PumpEvents();
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}
	}
}