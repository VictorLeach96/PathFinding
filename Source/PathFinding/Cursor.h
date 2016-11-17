#include "Header.h"

class Cursor
{
public:

	//Lifecycle
	void Update(int _deltaTime);
	void Draw(SDL_Surface* _screenSurface);

	//Constructor
	Cursor()
	{
		m_node.reset();
		m_node = make_shared<Node>(Blocked, newPoint(0, 0));
	}

	//Types
	void CycleType();
	NodeType GetType();

private:

	//Node
	shared_ptr<Node> m_node;
};