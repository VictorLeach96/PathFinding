#include "Header.h"

class Player
{
public:

	//Lifecycle
	void UpdateView();
	void Update(float _deltaTime);
	void Draw(SDL_Surface* _screenSurface);
	void DrawRoute(SDL_Surface* _screenSurface);

	//Constructor
	Player(shared_ptr<Node> _startNode)
	{
		m_currentNode = _startNode;
		UpdateView();
	}

	//State
	bool IsMoving();
	shared_ptr<Node> GetCurrentNode();
	shared_ptr<Node> GetNextNode();

	//Route
	void StartRoute(vector<shared_ptr<Node>> _route);
	void UpdateRoute(vector<shared_ptr<Node>> _newRoute);
	void StepRoute(float _deltaTime);
	void StopRoute();

private:

	//View
	SDL_Surface* m_surface;
	SDL_Rect m_bounds;

	//Route
	shared_ptr<Node> m_currentNode;
	vector<shared_ptr<Node>> m_route;
};