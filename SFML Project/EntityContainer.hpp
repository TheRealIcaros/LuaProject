#ifndef ENTITYCONTAINER_HPP
#define ENTITYCONTAINER_HPP

#include "Include.h"
#include "Enemy.hpp"
#include "Player.hpp"

class EntityContainer : public Drawable
{
private:
	Player* player;
	Enemy* *enemys;
	int nrOf;
	int cap;

public:
	EntityContainer(lua_State* L);
	~EntityContainer();
	void update(lua_State* L, float dt);	//(float dt, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;
};

#endif // !
