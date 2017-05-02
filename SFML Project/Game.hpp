#ifndef GAME_HPP
#define GAME_HPP

#include "Include.h"
#include "EntityContainer.hpp"

class Game : public Drawable
{
private:
	EntityContainer et;
	lua_State* L;
	Clock dt;

	int lookDirection;
public:
	Game(lua_State* L);
	~Game();
	void update(lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	//static int CheckMovement(lua_State* L);
};

#endif // !
