#ifndef GAME_HPP
#define GAME_HPP

#include "Include.h"
#include "EntityContainer.hpp"

class Game : public Drawable
{
private:
	/*RectangleShape start;
	RectangleShape editor;
	RectangleShape exit;*/

	lua_State* L;
	EntityContainer et;
	Clock dt;

	//int lookDirection;
	bool wasPressed;
	int selectedBlock;

public:
	Game();
	~Game();
	void update();
	void draw(RenderTarget &target, RenderStates states)const;

	static int CheckMovement(lua_State* L);
};

#endif // !
