#ifndef ENTITYCONTAINER_HPP
#define ENTITYCONTAINER_HPP

#include "Include.h"
#include "Enemy.hpp"
#include "Player.hpp"

class EntityContainer : public Drawable
{
private:
	Player player;
	//Enemy* *enemys2;
	vector<Enemy*> enemys;
	Clock hpClock;

	Texture texturePlayer;

public:
	EntityContainer();
	EntityContainer(lua_State* L);
	~EntityContainer();
	EntityContainer(const EntityContainer &originalObject);
	void operator=(const EntityContainer &originalObject);
	void update(lua_State* L, float dt);	//(float dt, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	void addEnemy(lua_State* L, float x = 200, float y = 200);
	void playerColition(int i);
	void wallColition();
	void restart(lua_State* L);
	void setPlayerSpawnPos(lua_State* L, Vector2i pos);
};

#endif // !
