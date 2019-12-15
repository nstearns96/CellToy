#include "Cell.h"

#include <math.h>

Cell::Cell()
{
}


Cell::~Cell()
{
}

void Cell::updatePosition(unsigned int dTime)
{
	posX += velX * dTime;
	posY += velY * dTime;

	extern int winWidth, winHeight;
	if (posX < 0)
	{
		velX = fabs(velX);
	}
	else if (posX + size > winWidth)
	{
		velX = -fabs(velX);
	}
	if (posY < 0)
	{
		velY = fabs(velY);
	}
	else if (posY + size > winHeight)
	{
		velY = -fabs(velY);
	}
}

SDL_Rect Cell::getRect()
{
	SDL_Rect result;

	result.x = round(posX);
	result.y = round(posY);
	result.w = round(size);
	result.h = result.w;

	return result;
}