#ifndef CELL_H
#define CELL_H


#include <SDL/SDL.h>

#include "Genome.h"

class Cell
{
public:
	Cell();
	~Cell();

	void updatePosition(unsigned int dTime);
	SDL_Rect getRect();

private:
	Genome genome;

	float food;
	float angle;
	float size = MAX_SIZE;

	union 
	{
		float position[2] = {0.0f, 0.0f};
		struct
		{
			float posX;
			float posY;
		};
	};

	union
	{
		float velocity[2] = {0.25f, 0.25f};
		struct
		{
			float velX;
			float velY;
		};
	};
};

#endif