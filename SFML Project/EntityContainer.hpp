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
	vector<Enemy*> enemys2;
	Clock hpClock;

public:
	EntityContainer();
	EntityContainer(lua_State* L);
	~EntityContainer();
	void update(lua_State* L, float dt);	//(float dt, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	void addEnemy(lua_State* L, float x = 200, float y = 200);
	void playerColition(int i);
	void wallColition();
};

#endif // !
