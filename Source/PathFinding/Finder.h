#include "Header.h"

class Finder
{
public:

	//Constructor
	Finder(vector<shared_ptr<Node>> _nodeList)
	{
		m_nodeList = _nodeList;
		isSuccessful = false;
	}

	//Calculate accessible path and return list of nodes to pass through
	bool StartFindPath(shared_ptr<Node> _startNode);
	bool StepFindPath(int _steps);
	bool WasSuccessful();
	vector<shared_ptr<Node>> GetFoundPath();

private:

	//State
	bool isSuccessful;

	//Special nodes
	shared_ptr<Node> m_startNode;
	shared_ptr<Node> m_goalNode;

	//Node lists
	vector<shared_ptr<Node>> m_nodeList;
	vector<shared_ptr<Node>> m_openList;
	vector<shared_ptr<Node>> m_closedList;
	vector<shared_ptr<Node>> m_routeList;

	//Helper functions
	shared_ptr<Node> FindSmallestNode(vector<shared_ptr<Node>> _list);
	bool PopNodeFromList(shared_ptr<Node> _node, vector<shared_ptr<Node>> &_list);
	bool ListContainsNode(shared_ptr<Node> _node, vector<shared_ptr<Node>> _list);
	vector<shared_ptr<Node>> FindNodeSuccessors(shared_ptr<Node> _node);
	int CalculateDistance(shared_ptr<Node> _startNode, shared_ptr<Node> _endNode);
};