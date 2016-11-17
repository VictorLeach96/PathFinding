#include "Header.h"

class Node
{
public:

	//Constructor
	Node(NodeType _type, SDL_Point _point)
	{
		//Types
		m_type = _type;

		//Costs
		m_hCost = 0;
		m_gCost = 0;
		m_fValue = 0;

		//View
		m_bounds = newRect(_point.x, _point.y, CELL_W, CELL_H);
		UpdateView();
	}

	//Views
	void SetCord(SDL_Point _point);
	SDL_Rect GetBounds();
	SDL_Point GetPoint();
	SDL_Point GetCord();
	void Draw(SDL_Surface* _screenSurface);

	//Types
	NodeType GetType();
	void SetType(NodeType _type);

	//Parent
	void UpdateParent(shared_ptr<Node> _parent);
	shared_ptr<Node> GetParent();

	//Costs
	int GetGCost();
	int GetTerrainCost();
	void UpdateCosts(int _hCost, int _gCost);
	int CalculateTotal();

private:

	//View
	SDL_Surface* m_surface;
	SDL_Rect m_bounds;

	void UpdateView();

	//Properties
	NodeType m_type;
	shared_ptr<Node> m_parent;
	int m_hCost;
	int m_gCost;
	int m_fValue;
};