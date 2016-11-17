#include "Header.h"

//Set the node poisition in screen space
void Node::SetCord(SDL_Point _point)
{
	m_bounds = newRect(_point.x, _point.y, CELL_W, CELL_H);
	UpdateView();
}

//Get bounds which have been offset by cell size
SDL_Rect Node::GetBounds()
{
	SDL_Rect offsetBounds = m_bounds;
	offsetBounds.x *= CELL_W;
	offsetBounds.y *= CELL_H;
	return offsetBounds;
}
SDL_Point Node::GetPoint()
{
	SDL_Point offsetPoint;
	offsetPoint.x = m_bounds.x * CELL_W;
	offsetPoint.y = m_bounds.y * CELL_H;
	return offsetPoint;
}
SDL_Point Node::GetCord()
{
	SDL_Point offsetPoint;
	offsetPoint.x = m_bounds.x;
	offsetPoint.y = m_bounds.y;
	return offsetPoint;
}

//Draw node view to screen surface
void Node::Draw(SDL_Surface* _screenSurface)
{
	SDL_BlitSurface(m_surface, NULL, _screenSurface, &GetBounds());
}

//Update node view with new type or bounds
void Node::UpdateView()
{
	//Create new surface with size from bounds
	m_surface = SDL_CreateRGBSurface(0, m_bounds.w, m_bounds.h, 32, 0, 0, 0, 0);

	//Draw border around node cell
	SDL_Rect* border = new SDL_Rect();
	border->x = 2;
	border->y = 2;
	border->w = m_bounds.w - 4;
	border->h = m_bounds.h - 4;
	SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 255, 255, 255));

	//Loop through each node type and set colour
	SDL_Surface* nodeImage;
	switch (m_type)
	{
	case Empty:
		SDL_FillRect(m_surface, border, SDL_MapRGB(m_surface->format, 230, 230, 230));
		break;
		
	case Blocked:
		SDL_FillRect(m_surface, border, SDL_MapRGB(m_surface->format, 0, 0, 0));
		break;

	case Easy:
		SDL_FillRect(m_surface, border, SDL_MapRGB(m_surface->format, 0, 255, 0));
		break;

	case Medium:
		SDL_FillRect(m_surface, border, SDL_MapRGB(m_surface->format, 255, 255, 0));
		break;

	case Hard:
		SDL_FillRect(m_surface, border, SDL_MapRGB(m_surface->format, 255, 0, 0));
		break;

	case Goal:
		SDL_FillRect(m_surface, border, SDL_MapRGB(m_surface->format, 0, 0, 0));

		//Overlay flag texture onto grid cell
		nodeImage = SDL_LoadBMP("Resources/flag.bmp");
		if(nodeImage == NULL)
		{
			cout << "Unable to load image " << SDL_GetError() << endl;
		}
		SDL_BlitSurface(nodeImage, NULL, m_surface, NULL);

		break;

	case Destroy:
		SDL_FillRect(m_surface, border, SDL_MapRGB(m_surface->format, 0, 0, 0));

		//Overlay flag texture onto grid cell
		nodeImage = SDL_LoadBMP("Resources/remove.bmp");
		if(nodeImage == NULL)
		{
			cout << "Unable to load image " << SDL_GetError() << endl;
		}
		SDL_BlitSurface(nodeImage, NULL, m_surface, NULL);

		break;
	}

}

//Setter and getters for the current node type
NodeType Node::GetType()
{
	return m_type;
}
void Node::SetType(NodeType _type)
{
	m_type = _type;
	UpdateView();
}

//Parent nodes to backtrack path
void Node::UpdateParent(shared_ptr<Node> _parent)
{
	m_parent = _parent;
}
shared_ptr<Node> Node::GetParent()
{
	return m_parent;
}

//Update cost values
int Node::GetGCost()
{
	return m_gCost + GetTerrainCost();
}
int Node::GetTerrainCost()
{
	//Pick a terrain cost for this node
	switch (m_type)
	{
	case Empty:
		return 0;
		break;
	case Blocked:
		return -1;
		break;
	case Easy:
		return 20;
		break;
	case Medium:
		return 50;
		break;
	case Hard:
		return 70;
		break;
	case Goal:
		return 0;
		break;
	}
	return -1;
}
void Node::UpdateCosts(int _hCost, int _gCost)
{
	//Perform cost calculations including terrain cost
	m_hCost = _hCost;
	m_gCost = _gCost;
	m_fValue = m_gCost + m_hCost;
}
int Node::CalculateTotal()
{
	return m_fValue;
}