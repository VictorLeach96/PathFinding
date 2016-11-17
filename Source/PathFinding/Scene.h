#include "Header.h"

class Scene
{
public:

	//Lifecycle
	void Draw(SDL_Surface* _screenSurface);
	bool Update(float _deltaTime);

	//Constructor
	Scene(Colour _backgroundColour)
	{
		isFinding = false;
		
		//Level
		m_backgroundColour = _backgroundColour;
		SetupGrid();
		
		//Actors
		m_cursor = make_shared<Cursor>();
		m_player = make_shared<Player>(m_nodes[0]);
		m_finder = make_shared<Finder>(m_nodes);
	}

	//Node management
	void PushNode(shared_ptr<Node> _node);
	void ClearNodes();

private:

	bool isFinding;

	//Actors
	shared_ptr<Cursor> m_cursor;
	shared_ptr<Player> m_player;
	shared_ptr<Finder> m_finder;

	//Level
	Colour m_backgroundColour;
	vector<shared_ptr<Node>> m_nodes;

	//Grid setup and cell clicks
	void SetupGrid();
	void ClickNode(Uint8 _buttonType, SDL_Point _point);
	void LeftClickNode(shared_ptr<Node> _node);
	void MiddleClickNode(shared_ptr<Node> _node);
	void RightClickNode(shared_ptr<Node> _node);
};