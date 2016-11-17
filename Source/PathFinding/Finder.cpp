#include "Header.h"

//====================-------------------- Path Finding Functions --------------------====================

//Start to find a new path from the starting node.
//Returns whether the calculation has started (Whether a goal exists in the node list)
bool Finder::StartFindPath(shared_ptr<Node> _startNode)
{
	//Reset variables
	isSuccessful = false;
	
	//Cleanup special nodes
	m_startNode.reset();
	m_goalNode.reset();

	//Cleanup node lists
	m_openList.clear();
	m_closedList.clear();
	m_routeList.clear();

	//Repopulate the start and goal nodes
	m_startNode = _startNode;
	for (auto node : m_nodeList)
	{
		if (node->GetType() == Goal)
		{
			m_goalNode = node;
			break;
		}
	}

	//No goal was found
	if (!m_goalNode)
	{
		return false;
	}

	//Add starting node to open list
	m_openList.push_back(_startNode);
	_startNode->UpdateParent(_startNode);

	return true;
}

//Perform a specific number of path finding calculation steps
//Return whether the path calculation has finished
bool Finder::StepFindPath(int _steps)
{
	//Perform the number of calculation steps specified
	for (int i=0; i<_steps; i++)
	{
		//Check whether the open list is empty (The path finding calculation has finished)
		if (m_openList.size() <= 0)
		{
			return true;
		}

		//Find smallest node in the open list and remove it
		auto currentNode = FindSmallestNode(m_openList);
		PopNodeFromList(currentNode, m_openList);

		//Check if the goal has been found
		if (currentNode == m_goalNode)
		{
			isSuccessful = true;
			
			//Loop through each of the nodes and build a path using their parents
			auto prevNode = currentNode;
			while (prevNode != m_startNode)
			{
				m_routeList.push_back(prevNode);
				prevNode = prevNode->GetParent();
			}
			m_routeList.push_back(m_startNode);

			//Swap around order of route
			reverse(m_routeList.begin(), m_routeList.end());

			return true;
		}

		//Add the current node to the closed list
		m_closedList.push_back(currentNode);

		//Loop through each of the current nodes successors
		for (auto succNode : FindNodeSuccessors(currentNode))
		{
			if (ListContainsNode(succNode, m_closedList))
			{
				continue;
			}

			//Calculate the potential new g cost of this node
			int newGCost = currentNode->GetGCost() + CalculateDistance(currentNode, succNode);

			//If the node does not exist yet in the open list then add it
			if (!ListContainsNode(succNode, m_openList))
			{
				m_openList.push_back(succNode);
			}

			//Compare the potential new g cost with the current node g cost to see whether its a cheaper path
			else if (newGCost >= succNode->GetGCost())
			{
				continue;
			}

			//Set parent to current node (To backtrack along path)
			succNode->UpdateParent(currentNode);

			//Calculate and update new node costs
			int newHCost = CalculateDistance(m_goalNode, succNode);
			succNode->UpdateCosts(newHCost, newGCost);
		}
	}

	return false;
}

//Return whether the goal was successfully reached or not
bool Finder::WasSuccessful()
{
	return isSuccessful;
}

//Returns a list of nodes to travel through to get from the start node to the end node
vector<shared_ptr<Node>>Finder:: GetFoundPath()
{
	return m_routeList;
}

//====================-------------------- Helper Functions --------------------====================

//Find and return the lowest cost node in a given list
shared_ptr<Node> Finder::FindSmallestNode(vector<shared_ptr<Node>> _list)
{
	//Loop through each node comparing each and always storing the smallest in a temp value
	auto smallest = _list[0];
	for (auto node : _list)
	{
		if (node->CalculateTotal() < smallest->CalculateTotal())
		{
			smallest = node;
		}
	}
	return smallest;
}

//Removes a the specific node in the given list returns whether it was found or not
bool Finder::PopNodeFromList(shared_ptr<Node> _node, vector<shared_ptr<Node>> &_list)
{
	for (int i=0; i<_list.size(); i++)
	{
		if (_list[i] == _node)
		{
			//If found remove the index from the vector
			_list.erase(_list.begin() + i);
			return true;
		}
	}
	return false;
}

//Search a specific node in the given list and return whether it exists
bool Finder::ListContainsNode(shared_ptr<Node> _node, vector<shared_ptr<Node>> _list)
{
	for (auto node : _list)
	{
		if (_node == node)
		{
			return true;
		}
	}
	return false;
}

//Find nodes which are adjacent a specific node using their distance
vector<shared_ptr<Node>> Finder::FindNodeSuccessors(shared_ptr<Node> _node)
{
	auto successors = vector<shared_ptr<Node>>();
	for (auto node : m_nodeList)
	{
		//Check whether node is next to start node using its distance calculation
		//Also make sure that the node is not a blocked type (-1 cost)
		int distance = CalculateDistance(_node, node);
		if (distance <= COST_X && distance <= COST_Y && node != _node && node->GetTerrainCost() >= 0)
		{
			successors.push_back(node);
		}
	}
	return successors;
}

//Calculate distance from node A to node B
int Finder::CalculateDistance(shared_ptr<Node> _startNode, shared_ptr<Node> _endNode)
{
	//Get world space point values from nodes
	SDL_Point startPoint = _startNode->GetCord();
	SDL_Point endPoint = _endNode->GetCord();

	//Calculate distance in x and y cords
	int deltaX = abs(startPoint.x - endPoint.x);
	int deltaY = abs(startPoint.y - endPoint.y);
	
	//Return total distance cost
	return (deltaX * COST_X) + (deltaY * COST_Y);

	//Calculate and apply diagonal distance between start and end points
	/*int deltaXY = abs(max(deltaX,deltaY) - abs(floor(deltaX - deltaY)));
	deltaX -= deltaXY;
	deltaY -= deltaXY;

	//Calculate and return total costs of distance
	int costX = deltaX * COST_X;
	int costY = deltaY * COST_Y;
	int costXY = deltaXY * COST_XY;
	return costX + costY + costXY;*/
}