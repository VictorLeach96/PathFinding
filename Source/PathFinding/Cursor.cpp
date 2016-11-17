#include "Header.h"

//Cycle through different node types
void Cursor::CycleType()
{
	//Check what current type currently is and change accordingly
	switch (m_node->GetType())
	{
	case Blocked:
		m_node->SetType(Destroy);
		break;
	case Destroy:
		m_node->SetType(Easy);
		break;
	case Easy:
		m_node->SetType(Medium);
		break;
	case Medium:
		m_node->SetType(Hard);
		break;
	case Hard:
		m_node->SetType(Blocked);
		break;
	}
}

NodeType Cursor::GetType()
{
	return m_node->GetType();
}

//====================-------------------- Lifecycle --------------------====================

void Cursor::Update(int _deltaTime)
{
	//Get mouse position
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);
	
	//Convert from screen space into co-ordinate space
	point.x = floor(point.x / CELL_W);
	point.y = floor(point.y / CELL_H);

	//Move to cursor node to co-ordinate
	m_node->SetCord(point);
}

void Cursor::Draw(SDL_Surface* _screenSurface)
{
	m_node->Draw(_screenSurface);
}