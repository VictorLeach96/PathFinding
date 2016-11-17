#include "Header.h"

//====================-------------------- Lifecycle --------------------====================

//Update node view with new type or bounds
void Player::UpdateView()
{
	m_bounds = newRect(0, 0, CELL_W - 10, CELL_H - 10);
	m_surface = SDL_CreateRGBSurface(0, m_bounds.w, m_bounds.h, 32, 0, 0, 0, 255);

	//Populate player surface view
	SDL_Surface* myImage = SDL_LoadBMP("Resources/player.bmp");
	SDL_SetColorKey(myImage, SDL_TRUE, SDL_MapRGB(myImage->format, 0, 0, 0));
	if(myImage == NULL)
	{
		cout << "Unable to load image " << SDL_GetError() << endl;
	}
	SDL_BlitSurface(myImage, NULL, m_surface, NULL);
}

//Update the bounds by following the next specific node
void Player::Update(float _deltaTime)
{
	StepRoute(_deltaTime);
}

//Draw node view to screen surface
void Player::Draw(SDL_Surface* _screenSurface)
{
	SDL_Rect offset = m_bounds;
	offset.x += 5;
	offset.y += 5;
	SDL_BlitSurface(m_surface, NULL, _screenSurface, &offset);
}

//Draw the route as lines
void Player::DrawRoute(SDL_Surface* _screenSurface)
{
	//Check if the player is moving and loop through each node in the route
	if (IsMoving())
	{
		for (int i=0; i<m_route.size(); i++)
		{
			//Draw a smaller transparent square ontop of node
			SDL_Rect bounds = m_route[i]->GetBounds();
			bounds.x += 14;
			bounds.y += 14;
			bounds.w -= 28;
			bounds.h -= 28;
			SDL_FillRect(_screenSurface, &bounds, SDL_MapRGB(_screenSurface->format, 223, 159, 159));
		}
	}
}

//====================-------------------- State --------------------====================

//return whether a path is currently being persued
bool Player::IsMoving()
{
	return m_route.size() > 0;
}

//Get the node which the player is currently on
shared_ptr<Node> Player::GetCurrentNode()
{
	return m_currentNode; 
}

//Get the next node that will be the target
shared_ptr<Node> Player::GetNextNode()
{
	if (m_route.size() > 0)
	{
		return m_route[0];
	}
	else
	{
		return NULL;
	}
}

//====================-------------------- Route --------------------====================

//Begin moving along a new route
void Player::StartRoute(vector<shared_ptr<Node>> _route)
{
	StopRoute();
	m_route = _route;

	//Check route is not empty
	if (_route.size() <= 0){
		return;
	}

	//Set starting position
	m_currentNode = m_route[0];
	m_bounds.x = m_currentNode->GetPoint().x;
	m_bounds.y = m_currentNode->GetPoint().y;
	m_route.erase(m_route.begin());
}

//Update route with new points
void Player::UpdateRoute(vector<shared_ptr<Node>> _newRoute)
{
	m_route = _newRoute;
}

//Step one frame towards the next node in the current route
void Player::StepRoute(float _deltaTime)
{
	//Make sure theres a current node
	if (!m_currentNode){
		return;
	}
	
	//Calculate delta position to next node
	float dx = m_currentNode->GetPoint().x - m_bounds.x;
	float dy = m_currentNode->GetPoint().y - m_bounds.y;
	
	//Calculate angle required for delta position
	float angle = atan2(dy, dx);

	//Calculate velocity for angle
	float vx = PLAYER_S * cos(angle);
	float vy = PLAYER_S * sin(angle);

	//Apply velocity to player position
	m_bounds.x += vx * _deltaTime;
	m_bounds.y += vy * _deltaTime;

	//Goal node was reached
	if (abs(dx) <= 2 && abs(dy) <= 2)
	{
		//Center itself in the cell
		m_bounds.x = m_currentNode->GetPoint().x;
		m_bounds.y = m_currentNode->GetPoint().y;

		//Make sure the route is not empty
		if (m_route.size() > 0){
			m_currentNode = m_route[0];
		
			//Remove the current node from route to start next node
			m_route.erase(m_route.begin());
		}
	}
}

//Clear all current route nodes
void Player::StopRoute()
{
	//Center itself in the cell
	m_bounds.x = m_currentNode->GetPoint().x;
	m_bounds.y = m_currentNode->GetPoint().y;

	//Clear route
	m_route.clear();
}