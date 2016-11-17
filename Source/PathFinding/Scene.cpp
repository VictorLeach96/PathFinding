#include "Header.h"

//Setup grid with default cells
void Scene::SetupGrid()
{
	//Loop through each grid cell
	for (int i=0; i<GRID_W; i++)
	{
		for (int z=0; z<GRID_H; z++)
		{
			//Create default grass node at grid cell
			PushNode(make_shared<Node>(Empty, newPoint(i, z)));
		}
	}
}

bool Scene::Update(float _deltaTime)
{
	//Update cursor position
	m_cursor->Update(_deltaTime);
	m_player->Update(_deltaTime);

	//Handle incoming keyboard and mouse events
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent)) 
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT:
			return false;
			break;

			//Mouse button has been pressed down
		case SDL_MOUSEBUTTONDOWN:
			ClickNode(incomingEvent.button.button, newPoint(incomingEvent.button.x, incomingEvent.button.y));
			break;

			//Mouse wheel has been scrolled one
		case SDL_MOUSEWHEEL:
			m_cursor->CycleType();
			break;
		}
	}

	//Perform path finding calculation
	if (isFinding)
	{
		//Perform 20 steps per frame
		if (m_finder->StepFindPath(20))
		{
			//Check if path finding has completed
			if (m_finder->WasSuccessful())
			{
				//Start new or update current route for player
				if (m_player->IsMoving())
				{
					m_player->UpdateRoute(m_finder->GetFoundPath());
				}
				else
				{
					m_player->StartRoute(m_finder->GetFoundPath());
				}
			}
			else
			{
				//If could not be found show message and stop player movement
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Oh dear...", "Could not find a valid path to the goal.", NULL);
				m_player->StopRoute();
			}

			isFinding = false;
		}
	}

	return true;
}

void Scene::Draw(SDL_Surface* _screenSurface)
{
	//Fill background with colour
	SDL_FillRect(_screenSurface, NULL, SDL_MapRGB(_screenSurface->format, m_backgroundColour.r, m_backgroundColour.b, m_backgroundColour.g));

	//Draw each node to screen
	for (auto node : m_nodes)
	{
		node->Draw(_screenSurface);
	}

	//Draw cursor
	m_cursor->Draw(_screenSurface);
	m_player->Draw(_screenSurface);
	m_player->DrawRoute(_screenSurface);
}

//Handle click events and find nodes which have been clicked
void Scene::ClickNode(Uint8 _buttonType, SDL_Point _point)
{
	//Loop through each node to check if clicked
	for (auto node : m_nodes)
	{
		//Get world space bounds from node
		SDL_Rect bounds = node->GetBounds();

		//Check if two rects intersect
		if (rectContainsPoint(bounds, _point))
		{
			//Check which mouse button has been pressed
			switch (_buttonType)
			{
			case SDL_BUTTON_LEFT:
				LeftClickNode(node);
				break;
			case SDL_BUTTON_MIDDLE:
				MiddleClickNode(node);
				break;
			case SDL_BUTTON_RIGHT:
				RightClickNode(node);
				break;
			}
		}
	}
}

//Node was clicked with left button, place the current node type there
void Scene::LeftClickNode(shared_ptr<Node> _node)
{
	//Match type to cursor replacing Destroy for Empty
	NodeType type = m_cursor->GetType();
	_node->SetType(type == Destroy ? Empty : type);

	//Check if player is currently moving
	if (m_player->IsMoving())
	{
		//Recalculate new path based on changes
		auto nextNode = m_player->GetNextNode();
		isFinding = m_finder->StartFindPath(nextNode != NULL ? nextNode : m_player->GetCurrentNode());
	}
}

//Node was clicked with middle button, calculate a path from here
void Scene::MiddleClickNode(shared_ptr<Node> _node)
{
	isFinding = m_finder->StartFindPath(_node);
	m_player->StopRoute();
}

//Node was clicked with right button, place goal there
void Scene::RightClickNode(shared_ptr<Node> _node)
{
	//Remove all other goal nodes
	for (auto node : m_nodes)
	{
		if (node->GetType() == Goal)
		{
			node->SetType(Empty);
		}
	}

	//Set node type to goal
	_node->SetType(Goal);

	//Start finding new goal
	isFinding = m_finder->StartFindPath(m_player->GetCurrentNode());
}

//Node management
void Scene::PushNode(shared_ptr<Node> _node)
{
	m_nodes.push_back(_node);
}
void Scene::ClearNodes()
{
	m_nodes.clear();
}