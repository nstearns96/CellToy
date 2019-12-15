#include <SDL/SDL.h>
#undef main

#include "CellToy.h"

#include <iostream>

#include "stb_image.h"

static Cell cell;
static SDL_Texture* cellTexture;

int winWidth, winHeight;

bool loadTexture(SDL_Renderer* mainRenderer)
{
	int width, height, numChannels;
	unsigned char* cellTextureData = stbi_load("Assets/Cell.png", &width, &height, &numChannels, 0);

	cellTexture = SDL_CreateTextureFromSurface(mainRenderer,
		SDL_CreateRGBSurfaceFrom(
			cellTextureData,
			width, height,
			32, numChannels*width,
			0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
		)
	);

	stbi_image_free(cellTextureData);

	return cellTexture == NULL;
}

void renderCell(SDL_Renderer* mainRenderer)
{
	SDL_Rect cellRect = cell.getRect();
	SDL_RenderCopy(mainRenderer, cellTexture, NULL, &cellRect);
}

bool init(SDL_Window*& window, SDL_Renderer*& renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(
			"Cell Toy",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			NULL, NULL,
			SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED
		);

		if (window != nullptr)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer != nullptr)
			{
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			}
			else
			{
				std::cout << "Failed to initialize renderer!\nSDL Error: " << SDL_GetError();
				return false;
			}
		}
		else
		{
			std::cout << "Failed to intialize window!\nSDL Error: " << SDL_GetError();
			return false;
		}
	}
	else
	{
		std::cout << "Failed to initialize SDL!\nSDL Error: " << SDL_GetError();
		return false;
	}

	return true;
}

void main()
{
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* mainRenderer = nullptr;
	if (init(mainWindow, mainRenderer))
	{
		SDL_SetRenderDrawColor(mainRenderer, 84, 230, 245, 255);

		unsigned int timeOld = SDL_GetTicks();
		unsigned int timeNew;
		unsigned int deltaTime;

		loadTexture(mainRenderer);

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

			SDL_GetWindowSize(mainWindow, &winWidth, &winHeight);

			timeNew = SDL_GetTicks();
			deltaTime = timeNew - timeOld;

			cell.updatePosition(deltaTime);

			SDL_RenderClear(mainRenderer);
			renderCell(mainRenderer);
			SDL_RenderPresent(mainRenderer);

			timeOld = timeNew;
		}
	}
}