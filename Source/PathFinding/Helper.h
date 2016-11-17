#include "Header.h"

//Types of nodes with their H value
enum NodeType
{
	Empty,
	Blocked,
	Easy,
	Medium,
	Hard,
	Goal,
	Destroy //Used for the cursor destory symbol
};

//RGB color struct for ease
struct Colour
{
	int r;
	int g;
	int b;
};

//Convenience initializers
Colour newColour(int _r, int _g, int _b);
SDL_Rect newRect(int _x, int _y, int _w, int _h);
SDL_Point newPoint(int _x, int _y);

//Geometry comparisons
bool rectContainsPoint(SDL_Rect _rect, SDL_Point _point);