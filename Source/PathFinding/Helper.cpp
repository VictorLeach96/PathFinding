#include "Header.h"

//Convenience initializers
Colour newColour(int _r, int _g, int _b)
{
	Colour col = Colour();
	col.r = _r;
	col.g = _g;
	col.b = _b;
	return col;
}

SDL_Rect newRect(int _x, int _y, int _w, int _h)
{
	SDL_Rect rect = SDL_Rect();
	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;
	return rect;
}

SDL_Point newPoint(int _x, int _y)
{
	SDL_Point point = SDL_Point();
	point.x = _x;
	point.y = _y;
	return point;
}

//Geometry comparisons
bool rectContainsPoint(SDL_Rect _rect, SDL_Point _point){
	if ((_point.x > _rect.x && _point.x < _rect.x + _rect.w) && (_point.y > _rect.y && _point.y < _rect.y + _rect.h))
	{
		return true;
	}
	else
	{
		return false;
	}
}